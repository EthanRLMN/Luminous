#include "WindowPanels/InspectorPanel.hpp"

#include "imgui.h"


void InspectorPanel::Render()
{
    IWindowPanel::Render();

    if (p_isOpen)
    {
        ImGui::Begin(p_windowIdentifier.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);

        ImGui::End();
    }
}
