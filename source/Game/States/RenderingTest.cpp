#include "RenderingTest.h"
#include "./Engine/Engine.hpp"
#include "./Engine/GameStateManager.hpp"
#include "./Engine/Input.hpp"
#include "./Engine/ShowCollision.h"
#include "./Engine/TextureManager.hpp"
#include "./Engine/Window.hpp"
#include <imgui.h>

#include "./CS200/IRenderer2D.hpp"
#include "./CS200/NDC.hpp"

#include "./Game/CS230_Final/Components/Grid.h"
#include "./Game/MainMenu.h"

#include <numbers>

RenderingTest::RenderingTest()
{
}

void RenderingTest::Load()
{
#ifdef _DEBUG
	AddGSComponent(new CS230::ShowCollision());
	AddGSComponent(new Grid());
#endif
	testTexture = Engine::GetTextureManager().Load("Assets/images/Test/mario.png");
}

void RenderingTest::Update([[maybe_unused]] double dt)
{
	if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape))
	{
		Engine::GetGameStateManager().PopState();
		Engine::GetGameStateManager().PushState<MainMenu>();
	}
	UpdateGSComponents(dt);
}

void RenderingTest::Draw()
{
	Engine::GetWindow().Clear(0x1a1a1aff);
	auto& renderer_2d = Engine::GetRenderer2D();

#ifdef _DEBUG
	GetGSComponent<Grid>()->Draw(Grid::DotColor::white);
#endif
	renderer_2d.BeginScene(CS200::build_ndc_matrix(Engine::GetWindow().GetSize()));
	testTexture->Draw(Math::TranslationMatrix(Math::to_vec2(translate)) * Math::RotationMatrix(static_cast<double>(rotate / 180 * std::numbers::pi_v<float>)) * Math::ScaleMatrix(Math::to_vec2(scale)));

	renderer_2d.EndScene();
}

void RenderingTest::DrawImGui()
{
	if(Engine::GetWindow().GetSize() != window_size){
		window_size = Engine::GetWindow().GetSize();
	}
	
	if (ImGui::Begin("Texture Controls"))
	{
		ImGui::SliderFloat("Scale X", &(scale.x), -20.f, 20.0f, "%.1f px/s");
		ImGui::SliderFloat("Scale Y", &(scale.y), -20.f, 20.0f, "%.1f px/s");
		ImGui::SliderFloat("Rotate", &rotate, 0.f, 360.0f, "%.1f px/s");
		ImGui::SliderFloat("Translate X", &(translate.x), 0.0f, static_cast<float>(window_size.x) - 100.f, "%.1f px/s");
		ImGui::SliderFloat("Translate Y", &(translate.y), 0.0f, static_cast<float>(window_size.y) - 100.f, "%.1f px/s");
	}
	ImGui::End();
}

void RenderingTest::Unload()
{
}