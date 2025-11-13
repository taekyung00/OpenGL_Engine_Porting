/**
 * \file
 * \author Taekyung Ho
 * \date 2025 Spring
 * \par CS230
 * \copyright DigiPen Institute of Technology
 */
#pragma once
#include "../../../Engine/GameState.hpp"
#include "../../../Engine/Engine.hpp"
#include "../../../Engine/Texture.hpp"

class NormalSandwich : public CS230::GameState
{
public:
    NormalSandwich()
    {
    }

    void          Load() override;
    void          Update(double dt) override;
    void          Unload() override;
    void          Draw() override;
    void          DrawImGui() override { };

    gsl::czstring GetName() const override
    {
        return "NormalSandwich";
    }

private:
    std::shared_ptr<CS230::Texture> texture;
};