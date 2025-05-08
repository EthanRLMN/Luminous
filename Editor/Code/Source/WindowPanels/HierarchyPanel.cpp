#include "WindowPanels/HierarchyPanel.hpp"

#include "imgui.h"


void HierarchyPanel::Render()
{
    IWindowPanel::Render();

    if (p_isOpen)
    {
        ImGui::Begin(p_windowIdentifier.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);

        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::MenuItem("Add New Entity"))
            {
            }
            ImGui::EndPopup();
        }

        ImGui::PopStyleColor();
        ImGui::End();
    }
}
