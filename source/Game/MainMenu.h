/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  MainMenu.h
Project:    CS230 Engine
Author:     Taekyung Ho
Created:    May 6, 2025
*/

#pragma once

#include "../Engine/Engine.hpp"
#include "../Engine/GameState.hpp"
#include "../Engine/Texture.hpp"
#include "../Engine/Font.hpp"

#include "Fonts.h"

class MainMenu : public CS230::GameState {
public:
    MainMenu();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() const override;
    

    gsl::czstring GetName() const override {
        return "MainMenu";
    }
    static constexpr unsigned int title_color = 0x9A2EFEFF;
    static constexpr unsigned int non_seleted_color = 0x3ADF00FF;
    static constexpr unsigned int seleted_color = 0xFFFFFFFF;
private:
enum class Option
    {
        cs230_final,
        exit
    };
    Option current_option;
    std::shared_ptr<CS230::Texture> title_texture;
    std::shared_ptr<CS230::Texture> cs230_final_texture;
    std::shared_ptr<CS230::Texture> exit_texture;

    unsigned int cs230_final_color ;
    unsigned int exit_color ;

    
    
    void update_textures();

};
