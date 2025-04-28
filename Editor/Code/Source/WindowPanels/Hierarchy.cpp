#include "WindowPanels/Hierarchy.hpp"

#include "imgui.h"


void Hierarchy::Draw()
{
    IWindowPanel::Draw();

    if (p_isOpen)
    {
        ImGui::Begin(p_windowIdentifier.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);

        ImGui::PopStyleColor();
        ImGui::End();
    }
}
