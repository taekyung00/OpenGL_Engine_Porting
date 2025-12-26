/**
 * \file
 * \author Taekyung Ho
 * \date 2025 Fall
 * \par CS200 Computer Graphics I
 * \copyright DigiPen Institute of Technology
 */

#include "Demo/DemoDepthPost.h"
#include "DemoDepthPost.h"
#include "Engine/TextureManager.h"
#include <algorithm>
#include <random>

#include "Engine/Collision.h"
#include "Engine/Input.h"
#include "Engine/Path.h"
#include "Engine/Random.h"
#include "Engine/TextureManager.h"
#include "Engine/Timer.h"
#include "Engine/Window.h"
#include <imgui.h>

#include "CS200/IRenderer2D.h"
#include "CS200/ImGuiHelper.h"
#include "CS200/NDC.h"
#include "CS200/RenderingAPI.h"

#include "OpenGL/Buffer.h"
#include "OpenGL/Environment.h"
#include "OpenGL/GL.h"

#include "Game/CS230_Final/Components/Grid.h"
#include "Game/MainMenu.h"

void DemoDepthPost::setupScreenTriangle()
{
	struct ScreenVertex
	{
		float x, y;
		float u, v;
	};

	const ScreenVertex vertices[] = {
		{ -1.0f, -1.0f, 0.0f, 0.0f },
		{  3.0f, -1.0f, 2.0f, 0.0f },
		{ -1.0f,	 3.0f, 0.0f, 2.0f },
	};

	screenVertexCount = static_cast<GLsizei>(std::ssize(vertices));

	screenVBO = OpenGL::CreateBuffer(OpenGL::BufferType::Vertices, std::as_bytes(std::span{ vertices }));

	const auto layout = {
		OpenGL::VertexBuffer{ screenVBO, { OpenGL::Attribute::Float2 } },
		  OpenGL::VertexBuffer{ screenVBO, { OpenGL::Attribute::Float2 } }
	};

	screenVAO = OpenGL::CreateVertexArrayObject(layout);
}

void DemoDepthPost::Load()
{
	Engine::GetWindow().ForceResize(default_window_size.x, default_window_size.y);
	Engine::GetWindow().SetWindowPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	auto& texture_manager = Engine::GetTextureManager();
	for (int i = 0; i < NUM_LAYERS; ++i)
	{
		background_layers[i].texture = texture_manager.Load("Assets/images/DemoDepthPost/background_" + std::to_string(i) + ".png");
		background_layers[i].depth	 = static_cast<float>(i) / NUM_LAYERS; // Depth from 0.0, 0.125, ..., 0.875
	}
	CS200::RenderingAPI::SetClearColor(CS200::WHITE);

	texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Batch);

	// Initialize FPS tracking
	LastTicks = SDL_GetTicks();

	// Initialize ducks
	duck_texture = texture_manager.Load("Assets/images/DemoDepthPost/duck.png");
	for (int i = 0; i < NUM_DUCKS; ++i)
	{
		ducks[i].position = { static_cast<double>(util::random(100, default_window_size.x - 100)), static_cast<double>(util::random(100, default_window_size.y - 100)) };
		uint8_t r		  = static_cast<uint8_t>(util::random(256));
		uint8_t g		  = static_cast<uint8_t>(util::random(256));
		uint8_t b		  = static_cast<uint8_t>(util::random(256));
		uint8_t a		  = static_cast<uint8_t>(util::random(100, 250)); // get transparency between 100 and 250
		ducks[i].color	  = CS200::pack_color(std::array<uint8_t, 4>{ r, g, b, a });
		ducks[i].depth	  = static_cast<float>(util::random(-0.9, -0.1)); // Depth between -0.9 to -0.1
	}

	// sort ducks by depth back to front(painter's algorithm)
	std::sort(std::begin(ducks), std::end(ducks), [](const Duck& left, const Duck& right) { return left.depth > right.depth; });

	// msaa settings
	const auto use_msaa = useMSAA ? OffscreenFramebuffer::MSAA::True : OffscreenFramebuffer::MSAA::False;
	offscreenBuffer.Initialize(default_window_size.x, default_window_size.y, use_msaa, MSAASamples);

	const std::filesystem::path screen_vert = assets::locate_asset("Assets/shaders/simple.vert");
	const std::filesystem::path screen_frag = assets::locate_asset("Assets/shaders/simple-texture.frag");
	screenShader							= OpenGL::CreateShader(screen_vert, screen_frag);

	setupScreenTriangle();

	postProcessing.Initialize(default_window_size.x, default_window_size.y);

	if (useMSAA)
    {
        GL::Enable(GL_MULTISAMPLE);
    }
}

void DemoDepthPost::Update([[maybe_unused]] double dt)
{
	// Update FPS tracker
	const Uint32 currentTicks = SDL_GetTicks();
	const Uint32 deltaTicks	  = currentTicks - LastTicks;
	const double deltaSeconds = deltaTicks / 1000.0;
	LastTicks				  = currentTicks;
	FPSTracker.Update(deltaSeconds);

	if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape))
	{
		Engine::GetGameStateManager().PopState();
		Engine::GetGameStateManager().PushState<MainMenu>();
	}
}

void DemoDepthPost::Unload()
{
	offscreenBuffer.Shutdown();
    postProcessing.Shutdown();
	if (screenVAO != 0)
    {
        GL::DeleteVertexArrays(1, &screenVAO);
        screenVAO = 0;
    }
    if (screenVBO != 0)
    {
        GL::DeleteBuffers(1, &screenVBO);
        screenVBO = 0;
    }
    if (screenShader.Shader != 0)
    {
        OpenGL::DestroyShader(screenShader);
    }
}

void DemoDepthPost::Draw()
{
	CS200::RenderingAPI::Clear();
	
	// opaque background layers
	GL::DepthMask(GL_TRUE); // enable depth write
	GL::DepthFunc(GL_LESS); // set depth function to less
	auto			  renderer_2d = Engine::GetTextureManager().GetRenderer2D();
	const Math::ivec2 window_size = Engine::GetWindow().GetSize();
	CS200::RenderingAPI::SetViewport(window_size, { 0, 0 });

	renderer_2d->BeginScene(CS200::build_ndc_matrix(window_size));
	for (const auto& layer : background_layers)
	{
		layer.texture->Draw(Math::TransformationMatrix(), 0xFFFFFFFF, layer.depth);
	}
	// transparent ducks
	GL::DepthMask(GL_FALSE); // disable depth write
	for (const auto& duck : ducks)
	{
		duck_texture->Draw(Math::TranslationMatrix(duck.position), duck.color, duck.depth);
	}
	GL::DepthMask(GL_TRUE); // enable depth write
	renderer_2d->EndScene();
}

void DemoDepthPost::DrawImGui()
{
	ImGui::Begin("Demo Depth & Post-Processing Controls");
	// Display FPS at the top
	ImGui::Text("FPS: %d", static_cast<int>(FPSTracker));
	ImGui::Separator();

	ImGui::SeparatorText("Depth Settings");

	if (ImGui::Button("Sort as Painters Algorithm"))
	{
		std::sort(std::begin(background_layers), std::end(background_layers), [](const BackGroundLayer& left, const BackGroundLayer& right) { return left.depth > right.depth; });
	}

	if (ImGui::Button("Sort as Front to Back"))
	{
		std::sort(
			std::begin(background_layers), std::end(background_layers),
			[](const BackGroundLayer& left, const BackGroundLayer& right)
			{
				return left.depth < right.depth; // then smaller depth drawn first, and frag of larger depth gonna be skipped over by depth test, and hopefully save effort of fragment shader
			});
	}

	if (ImGui::Button("Sort Randomly"))
	{
		std::random_device rd;
		std::mt19937	   g(rd());
		std::shuffle(std::begin(background_layers), std::end(background_layers), g);
	}
	ImGui::End();
}
