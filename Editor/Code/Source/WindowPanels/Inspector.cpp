#include "WindowPanels/Inspector.hpp"

#include "imgui.h"


void Inspector::Draw()
{
    IWindowPanel::Draw();

    if (p_isOpen)
    {
        ImGui::Begin(p_windowIdentifier.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);

        ImGui::End();
    }
}
