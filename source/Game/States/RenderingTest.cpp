/**
 * \file
 * \author Taekyung Ho
 * \date 2025 Fall
 * \par CS200 Computer Graphics I
 * \copyright DigiPen Institute of Technology
 */
#include "RenderingTest.h"
#include "Engine/Camera.h"
#include "Engine/Engine.hpp"
#include "Engine/GameStateManager.hpp"
#include "Engine/Input.hpp"
#include "Engine/ShowCollision.h"
#include "Engine/TextureManager.hpp"
#include "Engine/Window.hpp"

#include "Engine/Particle.h"
#include <imgui.h>
#include <numbers>

#include "./CS200/IRenderer2D.hpp"
#include "./CS200/NDC.hpp"
#include "CS200/RenderingAPI.hpp"

#include "Game/CS230_Final/Components/Grid.h"
#include "Game/MainMenu.h"
#include "Game/Particles.h"

#include "Demo/DemoSceneShowcase/Samurai.h"

#include <OpenGL/GL.hpp>

void RenderingTest::Load()
{
	Engine::GetTextureManager().SwitchRenderer(CS230::TextureManager::RendererType::Batch);
#ifdef DEVELOPER_VERSION
	AddGSComponent(new CS230::ShowCollision());
	AddGSComponent(new Grid());
#endif
	AddGSComponent(new CS230::GameObjectManager);
	testTexture = Engine::GetTextureManager().Load("Assets/images/Test/mario.png");

	samurai = new Samurai();
	GetGSComponent<CS230::GameObjectManager>()->Add(samurai);
	AddGSComponent(new CS230::ParticleManager<Particles::Tears>());
	AddGSComponent(new CS230::ParticleManager<Particles::Shining>());
	AddGSComponent(new CS230::ParticleManager<Particles::Flame>());
	AddGSComponent(new CS230::Camera(Math::rect{ static_cast<Math::vec2>(Engine::GetWindow().GetSize()) * 0.3, static_cast<Math::vec2>(Engine::GetWindow().GetSize()) * 0.7 }));
	// GetGSComponent<CS230::Camera>()->SetPositionOffset({300.0,300.0});
	GetGSComponent<CS230::Camera>()->SetLimit({
		{	  0,	 0 },
		  { 3000, 3000 }
	 });
	GetGSComponent<CS230::Camera>()->SetAnchoring() = true;
	GetGSComponent<CS230::Camera>()->SetPosition(samurai->GetPosition());
	GetGSComponent<CS230::Camera>()->SetFirstPersonView() = first_person_view;
	GetGSComponent<CS230::Camera>()->SetScale(camera_scale);
	GetGSComponent<CS230::Camera>()->SetRotation(camera_rotation);

	CS200::RenderingAPI::SetClearColor(CS200::WHITE);
}

void RenderingTest::Update([[maybe_unused]] double dt)
{
	UpdateGSComponents(dt);

	CS230::Camera* camera = GetGSComponent<CS230::Camera>();

	camera->Update(samurai->GetPosition());
	camera->SetRotation(samurai->GetRotation());


	GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);
	if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape)) // very bottom!!
	{
		Engine::GetGameStateManager().PopState();
		Engine::GetGameStateManager().PushState<MainMenu>();
		return;
	}
}

void RenderingTest::Draw()
{
	window_size = Engine::GetWindow().GetSize();
	CS200::RenderingAPI::Clear();
	auto		  renderer_2d		  = Engine::GetTextureManager().GetRenderer2D();
	constexpr int num_subwindows_wide = 2;
	constexpr int num_subwindows_high = 2;
	Math::ivec2	  subwindow_size	  = { window_size.x / num_subwindows_wide, window_size.y / num_subwindows_high };

	for (int i = 0; i < num_subwindows_high; ++i)
	{
		for (int j = 0; j < num_subwindows_wide; ++j)
		{
			GL::Viewport(static_cast<GLint>(subwindow_size.x * j), static_cast<GLint>(subwindow_size.x * i), static_cast<GLint>(subwindow_size.x), static_cast<GLint>(subwindow_size.y));

			renderer_2d->BeginScene(CS200::build_ndc_matrix(subwindow_size, true) * GetGSComponent<CS230::Camera>()->GetMatrix());
			GetGSComponent<CS230::GameObjectManager>()->DrawAll(Math::TransformationMatrix());

#ifdef DEVELOPER_VERSION
			GetGSComponent<Grid>()->Draw(Grid::DotColor::black, 0.2f);
#endif
			testTexture->Draw(
				Math::TranslationMatrix(Math::to_vec2(translate)) * Math::RotationMatrix(static_cast<double>(rotate / 180 * std::numbers::pi_v<float>)) * Math::ScaleMatrix(Math::to_vec2(scale)));
			renderer_2d->EndScene();
		}
	}

	GL::Viewport(0, 0, static_cast<GLint>(window_size.x), static_cast<GLint>(window_size.y));
	renderer_2d->BeginScene(CS200::build_ndc_matrix(window_size));
	renderer_2d->DrawRectangle(Math::TranslationMatrix((window_size / 2)) * Math::ScaleMatrix(window_size), CS200::CLEAR, CS200::BLUE, 5.0, 0.0f);
	renderer_2d->DrawLine(
		Math::vec2{ 0.0, static_cast<double>(window_size.y) / num_subwindows_high }, Math::vec2{ static_cast<double>(window_size.x), static_cast<double>(window_size.y) / num_subwindows_high },
		CS200::RED, 2.5, 0.0f);
	renderer_2d->DrawLine(
		Math::vec2{ static_cast<double>(window_size.x) / num_subwindows_wide, 0 }, Math::vec2{ static_cast<double>(window_size.x) / num_subwindows_wide, static_cast<double>(window_size.y) },
		CS200::RED, 2.5, 0.0f);
	renderer_2d->EndScene(); 
}

void RenderingTest::DrawImGui()
{
	if (Engine::GetWindow().GetSize() != window_size)
	{
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

	if (ImGui::Begin("Particle Controls"))
	{
		if (ImGui::Button("Shine"))
		{
			const auto shining_particle = Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Shining>>();
			if (!shining_particle)
			{
				throw std::logic_error("no shining particle");
			}
			shining_particle->Emit(10, Math::to_vec2(translate), { 0, 0 }, { 20, 20 }, std::numbers::pi * 2);
		}
		ImGui::SameLine();

		if (ImGui::Button("Tears"))
		{
			const auto tears_particle = Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Tears>>();
			if (tears_particle)
			{
				tears_particle->Emit(10, Math::to_vec2(translate), { 0, 0 }, { -20, -20 }, std::numbers::pi * 2);
			}
		}

		ImGui::SameLine();

		if (ImGui::Button("Flame"))
		{
			const auto tears_particle = Engine::GetGameStateManager().GetGSComponent<CS230::ParticleManager<Particles::Flame>>();
			if (tears_particle)
			{
				tears_particle->Emit(1, Math::to_vec2(translate), { 0, 0 }, { 0, 20 }, std::numbers::pi * 2, 0xF36301FF);
			}
		}
	}
	ImGui::End();

	ImGui::Begin("Renderer Settings");
	ImGui::Separator();

	// Renderer selection
	auto&	   texture_manager		 = Engine::GetTextureManager();
	const auto current_renderer_type = texture_manager.GetCurrentRendererType();
	// const auto renderer_2d = texture_manager.GetRenderer2D();
	ImGui::Text("Renderer:");

	if (ImGui::RadioButton("Immediate", current_renderer_type == CS230::TextureManager::RendererType::Immediate))
	{
		texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Immediate);
	}

	ImGui::SameLine();

	if (ImGui::RadioButton("Batch", current_renderer_type == CS230::TextureManager::RendererType::Batch))
	{
		texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Batch);
	}

	ImGui::SameLine();
	if (ImGui::RadioButton("Instanced", current_renderer_type == CS230::TextureManager::RendererType::Instanced))
	{
		texture_manager.SwitchRenderer(CS230::TextureManager::RendererType::Instanced);
	}
	ImGui::Separator();

	ImGui::End();

	ImGui::Begin("Camera Controls");
	// float fcamera_rotation = static_cast<float>(camera_rotation);
	// if (ImGui::SliderFloat("Camera Rotation", &fcamera_rotation, -180.f, 180.f))
	//{
	//	camera_rotation = static_cast<double>(fcamera_rotation);
	//	GetGSComponent<CS230::Camera>()->SetRotation(static_cast<double>(camera_rotation / 180.f * std::numbers::pi_v<float>));
	// }
	Math::fvec2 fcamera_scale = Math::to_fvec2(camera_scale);
	bool		scale_changed = false;
	if (ImGui::SliderFloat("Camera ScaleX", &fcamera_scale.x, 0.1f, 10.f))
	{
		camera_scale.x = static_cast<double>(fcamera_scale.x);
		scale_changed  = true;
	}
	if (ImGui::SliderFloat("Camera ScaleY", &fcamera_scale.y, 0.1f, 10.f))
	{
		camera_scale.y = static_cast<double>(fcamera_scale.y);
		scale_changed  = true;
	}
	if (scale_changed)
	{
		GetGSComponent<CS230::Camera>()->SetScale(camera_scale);
	}

	if (ImGui::Checkbox("First Person View", &first_person_view))
	{
		GetGSComponent<CS230::Camera>()->SetFirstPersonView() = first_person_view;
	}
	ImGui::End();
}

void RenderingTest::Unload()
{
	GetGSComponent<CS230::GameObjectManager>()->Unload();
	ClearGSComponents();
}