#include "WindowPanels/InspectorWindow.hpp"

#include "imgui.h"


void InspectorWindow::Draw()
{
    if (p_isOpen)
    {
        ImGui::SetNextWindowPos(ImVec2(1950, 670), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(590, 700), ImGuiCond_FirstUseEver);

        ImGui::Begin(p_windowIdentifier.c_str(), &p_isOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);

        ImGui::PopStyleColor();
        ImGui::End();
    }
}
