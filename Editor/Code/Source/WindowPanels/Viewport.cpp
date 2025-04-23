#include "imgui.h"

#include "WindowPanels/Viewport.hpp"


void Viewport::Draw()
{
    ImGui::SetNextWindowPos(ImVec2(5, 70), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(1935, 880), ImGuiCond_FirstUseEver);

    ImGui::Begin(p_windowIdentifier.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 5.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);

    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    ImGui::End();
}
