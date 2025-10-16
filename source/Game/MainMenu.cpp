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
#include "../Game/CS230_Final/States/Project.h"
#include "../CS200/IRenderer2D.hpp"
#include "../CS200/NDC.hpp"
#include "../CS200/RenderingAPI.hpp"
#include "../Demo/DemoBufferTypes.hpp"
#include "../Demo/DemoCS230Textures.hpp"
#include "../Demo/DemoFramebuffer.hpp"
#include "../Demo/DemoShapes.hpp"
#include "../Demo/DemoText.hpp"
#include "../Demo/DemoTexturing.hpp"
#include "../Demo/DemoVAO.hpp"
#include "../Engine/GameStateManager.hpp"
#include "../Engine/Input.hpp"
#include "../Engine/TextManager.hpp"
#include "../Engine/Window.hpp"
#include "States.h"
#include <imgui.h>

MainMenu::MainMenu() : current_option(Option::cs230_final)
{
}

void MainMenu::Load()
{
    CS200::RenderingAPI::SetClearColor(0x000000FF);
    update_colors();
}

void MainMenu::Update([[maybe_unused]] double dt)
{
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Down))
    {
        switch (current_option)
        {
            case MainMenu::Option::cs230_final: current_option = Option::exit; break;
            case MainMenu::Option::exit: current_option = Option::cs230_final; break;
        }
    }

    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up))
    {
        switch (current_option)
        {
            case MainMenu::Option::cs230_final: current_option = Option::exit; break;
            case MainMenu::Option::exit: current_option = Option::cs230_final; break;
        }
    }
    update_colors();
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Enter))
    {
        switch (current_option)
        {
            case MainMenu::Option::cs230_final:
                Engine::GetGameStateManager().PopState();
                 Engine::GetGameStateManager().PushState<Project>();
                break;
            case MainMenu::Option::exit: Engine::GetGameStateManager().PopState(); break;
        }
    }
}

void MainMenu::Unload()
{
}

void MainMenu::Draw()
{
    CS200::RenderingAPI::Clear();
    auto& renderer_2d = Engine::GetRenderer2D();
    renderer_2d.BeginScene(CS200::build_ndc_matrix(Engine::GetWindow().GetSize()));

    auto& text_manager = Engine::GetTextManager();
    auto  window_size  = Engine::GetWindow().GetSize();
    text_manager.DrawText(
        "Game Porting", Math::vec2{ static_cast<double>(window_size.x / 2 - 300 / 2 - 100), static_cast<double>(Engine::GetWindow().GetSize().y - 69 - 100) }, Fonts::Outlined, { 1.5, 1.5 },
        title_color);
    text_manager.DrawText(
        "CS230 Final", Math::vec2{ static_cast<double>(window_size.x / 2 - 300 / 2), static_cast<double>(window_size.y - 68 * 2 - 200) }, Fonts::Outlined, { 1.0, 1.0 }, cs230_final_color);
    text_manager.DrawText("Exit", Math::vec2{ static_cast<double>(window_size.x / 2 - 300 / 2), static_cast<double>(window_size.y - 68 * 3 - 200) }, Fonts::Outlined, { 1.0, 1.0 }, exit_color);
    // title_texture->Draw(Math::TranslationMatrix(Math::ivec2{
    //	Engine::GetWindow().GetSize().x/2  - title_texture->GetSize().x/2 - 100,
    //	Engine::GetWindow().GetSize().y - title_texture->GetSize().y - 100 }) * Math::ScaleMatrix(1.5));

    // cs230_final_texture->Draw(Math::TranslationMatrix(Math::ivec2{
    //	Engine::GetWindow().GetSize().x / 2 - cs230_final_texture->GetSize().x / 2,
    //	Engine::GetWindow().GetSize().y - cs230_final_texture->GetSize().y - 200 }));


    // exit_texture->Draw(Math::TranslationMatrix(Math::ivec2{
    //	Engine::GetWindow().GetSize().x / 2 - 10 - exit_texture->GetSize().x / 2,
    //	Engine::GetWindow().GetSize().y - exit_texture->GetSize().y - 400 }));

    renderer_2d.EndScene();
}

void MainMenu::DrawImGui()
{
    if (ImGui::Begin("Demo Controls"))
    {
        if (ImGui::Button("Switch to Demo DemoBufferTypes"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoBufferTypes>();
        }
        if (ImGui::Button("Switch to Demo DemoCS230Textures"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoCS230Textures>();
        }
        if (ImGui::Button("Switch to Demo DemoFramebuffer"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoFramebuffer>();
        }
        if (ImGui::Button("Switch to Demo DemoShapes"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoShapes>();
        }
        if (ImGui::Button("Switch to Demo DemoText"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoText>();
        }
        if (ImGui::Button("Switch to Demo DemoTexturing"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoTexturing>();
        }
        if (ImGui::Button("Switch to Demo DemoVAO"))
        {
            Engine::GetGameStateManager().PopState();
            Engine::GetGameStateManager().PushState<DemoVAO>();
        }
    }
    ImGui::End();
}

gsl::czstring MainMenu::GetName() const
{
    return "MainMenu";
}

void MainMenu::update_colors()
{
    switch (current_option)
    {
        case MainMenu::Option::cs230_final:
            cs230_final_color = seleted_color;
            exit_color        = non_seleted_color;
            break;
        case MainMenu::Option::exit:
            cs230_final_color = non_seleted_color;
            exit_color        = seleted_color;
            break;
    }
}
