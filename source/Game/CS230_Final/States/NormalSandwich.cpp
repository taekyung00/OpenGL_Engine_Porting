/**
 * \file
 * \author Taekyung Ho
 * \date 2025 Spring
 * \par CS230
 * \copyright DigiPen Institute of Technology
 */
#include "NormalSandwich.h"
#include "Project.h"
#include "../../MainMenu.h"
#include "../../../Engine/TextureManager.hpp"
#include "../../../Engine/GameStateManager.hpp"
#include "../../../Engine/Input.hpp"
#include "../../../Engine/Window.hpp"

#include "CS200/NDC.hpp"
void NormalSandwich::Load() {
    texture = Engine::GetTextureManager().Load("Assets/images/CS230_Final/NormalSandwich.png");
}

void NormalSandwich::Update([[maybe_unused]] double dt) {
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Escape)) {
        Engine::GetGameStateManager().PopState();
        Engine::GetGameStateManager().PushState<MainMenu>();
    }

    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R)) {
        Engine::GetGameStateManager().PopState();
        Engine::GetGameStateManager().PushState<Project>();
    }
}

void NormalSandwich::Unload() {

}

void NormalSandwich::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
	auto renderer_2d = Engine::GetTextureManager().GetRenderer2D();
	renderer_2d->BeginScene(CS200::build_ndc_matrix(Engine::GetWindow().GetSize()));
    texture->Draw(Math::TransformationMatrix());

    renderer_2d->EndScene();
}