#include "FileExplorerWindow.hpp"

#include "imgui.h"

void FileExplorerWindow::Draw()
{
    ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);
    ImGui::SetNextWindowSize({ 1920, 215 }, ImGuiCond_FirstUseEver);

    if (p_isOpen && ImGui::Begin(p_windowIdentifier.c_str(), &p_isOpen, ImGuiWindowFlags_NoCollapse))
    {
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
        ImGui::End();
    }
    ImGui::PopStyleColor();
}
