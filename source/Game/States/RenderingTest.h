/**
 * \file
 * \author Taekyung Ho
 * \date 2025 Fall
 * \par CS200 Computer Graphics I
 * \copyright DigiPen Institute of Technology
 */
#pragma once
#include <memory>

#include "./Engine/GameState.hpp"
#include "./Engine/Texture.hpp"

#include "Demo/DemoSceneShowcase/Samurai.h"


class RenderingTest : public CS230::GameState
{
public:
	RenderingTest() = default;
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;
	void DrawImGui() override;

	gsl::czstring GetName() const override
	{
		return "Rendering Test";
	}

private:
	Samurai*						samurai = nullptr;
	std::shared_ptr<CS230::Texture> testTexture = nullptr;
	Math::fvec2 scale = {1.f,1.f};
	float rotate = 0.f;
	Math::fvec2 translate = {0.f,0.f};
	Math::ivec2 window_size;

	double camera_rotation = 0.0;
	Math::vec2 camera_scale = { 1.0, 1.0 };

	bool first_person_view = true;
};