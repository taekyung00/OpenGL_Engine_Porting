/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  MainMenu.cpp
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    May 6, 2025
*/

#include "MainMenu.h"
#include "States.h"
#include "../Engine/Input.hpp"
#include "../Engine/GameStateManager.hpp"
#include "../Engine/Window.hpp"

MainMenu::MainMenu() : 
	current_option(Option::cs230_final),
	title_texture(nullptr){}

void MainMenu::Load()
{
	title_texture = (Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("CS230 Engine Test", title_color));
	update_textures();
}

void MainMenu::Update([[maybe_unused]] double dt)
{
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Down)) {
		switch (current_option)
		{
		case MainMenu::Option::cs230_final:
			current_option = Option::exit;			
			break;
		case MainMenu::Option::exit:
			current_option = Option::cs230_final;
			break;
		}
	}

	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up)) {
		switch (current_option)
		{
		case MainMenu::Option::cs230_final :
			current_option = Option::exit;
			break;
		case MainMenu::Option::exit:
			current_option = Option::cs230_final;
			break;
		}
	}
	update_textures();
	if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Enter)) {
		switch (current_option)
		{
		case MainMenu::Option::cs230_final:
			Engine::GetGameStateManager().PopState();
            // Engine::GetGameStateManager().PushState<DemoTexturing>();
			break;
		case MainMenu::Option::exit:
			Engine::GetGameStateManager().PopState();
			break;
		}
	}
}

void MainMenu::Unload()
{
}

void MainMenu::Draw() const
{
	Engine::GetWindow().Clear(0x000000FF);
	title_texture->Draw(Math::TranslationMatrix(Math::ivec2{ 
		Engine::GetWindow().GetSize().x/2  - title_texture->GetSize().x/2 - 100, 
		Engine::GetWindow().GetSize().y - title_texture->GetSize().y - 100 }) * Math::ScaleMatrix(1.5));

	cs230_final_texture->Draw(Math::TranslationMatrix(Math::ivec2{
		Engine::GetWindow().GetSize().x / 2 - cs230_final_texture->GetSize().x / 2,
		Engine::GetWindow().GetSize().y - cs230_final_texture->GetSize().y - 200 }));


	exit_texture->Draw(Math::TranslationMatrix(Math::ivec2{
		Engine::GetWindow().GetSize().x / 2 - 10 - exit_texture->GetSize().x / 2,
		Engine::GetWindow().GetSize().y - exit_texture->GetSize().y - 400 }));

}

void MainMenu::update_textures()
{
	switch (current_option)
	{
	case MainMenu::Option::cs230_final:
		cs230_final_color = seleted_color;
		exit_color = non_seleted_color;
		break;
	case MainMenu::Option::exit:
		cs230_final_color = seleted_color;
		exit_color = seleted_color;
		break;
	}
	cs230_final_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("CS230_Final", cs230_final_color);
	exit_texture = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("Exit", exit_color);

}
