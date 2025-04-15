#include "WindowPanels/FileExplorerWindow.hpp"

#include "imgui.h"

void FileExplorerWindow::Draw()
{
    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
    ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size, ImGuiCond_FirstUseEver);

    if (p_isOpen)
    {
        ImGui::Begin(p_windowIdentifier.c_str(), &p_isOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);
        if (ImGui::BeginTable("table1", 3, ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_BordersOuterV, { 0, 0 }))
        {
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_None, 0);
            ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_None, 0);
            ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_None, 0);
            ImGui::TableHeadersRow();
            ImGui::TableNextRow(0, 150);
            ImGui::TableSetColumnIndex(0);

            ImGui::EndTable();
        }
        ImGui::PopStyleColor();
        ImGui::End();
    }
}
