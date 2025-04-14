#include "InspectorWindow.hpp"

#include "imgui.h"

void InspectorWindow::Draw()
{
    ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);
    ImGui::SetNextWindowSize({ 1920, 1080 }, ImGuiCond_FirstUseEver);

    if (p_isOpen && ImGui::Begin(p_windowIdentifier.c_str(), &p_isOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar))
    {
        ImGui::End();
    }
    ImGui::PopStyleColor();
}
