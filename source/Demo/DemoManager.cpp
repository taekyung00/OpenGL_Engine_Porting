#include "DemoManager.hpp"
#include "DemoBufferTypes.hpp"
#include "DemoCS230Textures.hpp"
#include "DemoFramebuffer.hpp"
#include "DemoShapes.hpp"
#include "DemoText.hpp"
#include "DemoTexturing.hpp"
#include "DemoVAO.hpp"
#include "Engine/GameStateManager.hpp"
#include <imgui.h>

namespace CS200
{
    void DemoManager::UpdateDemo()
    {
        if (ImGui::Begin("Demo Control"))
        {
            if (ImGui::Button("DemoBufferTypes"))
            {
                Engine::GetGameStateManager().PopState();
                Engine::GetGameStateManager().PushState<DemoBufferTypes>();
            }
            else if (ImGui::Button("DemoCS230Textures"))
            {
                Engine::GetGameStateManager().PopState();
                Engine::GetGameStateManager().PushState<DemoCS230Textures>();
            }
            else if (ImGui::Button("DemoFramebuffer"))
            {
                Engine::GetGameStateManager().PopState();
                Engine::GetGameStateManager().PushState<DemoFramebuffer>();
            }
            else if (ImGui::Button("DemoShapes"))
            {
                Engine::GetGameStateManager().PopState();
                Engine::GetGameStateManager().PushState<DemoShapes>();
            }
            else if (ImGui::Button("DemoText"))
            {
                Engine::GetGameStateManager().PopState();
                Engine::GetGameStateManager().PushState<DemoText>();
            }
            else if (ImGui::Button("DemoTexturing"))
            {
                Engine::GetGameStateManager().PopState();
                Engine::GetGameStateManager().PushState<DemoTexturing>();
            }
            else if (ImGui::Button("DemoVAO"))
            {
                Engine::GetGameStateManager().PopState();
                Engine::GetGameStateManager().PushState<DemoVAO>();
            }
            ImGui::End();
        }
    }

} // namespace CS200
