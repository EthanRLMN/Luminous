#include "WindowPanels/InspectorWindow.hpp"

#include "imgui.h"

void InspectorWindow::Draw()
{
    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
    ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size, ImGuiCond_FirstUseEver);

    if (p_isOpen)
    {
        ImGui::Begin(p_windowIdentifier.c_str(), &p_isOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);

        ImGui::PopStyleColor();
        ImGui::End();
    }
}
