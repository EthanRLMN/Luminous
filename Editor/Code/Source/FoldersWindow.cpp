#include "FoldersWindow.hpp"
#include "MainWindow.hpp"

void FoldersWindow::Draw()
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);
	ImGui::SetNextWindowSize({ 1920, 215 }, ImGuiCond_FirstUseEver);

	if (m_isOpen && ImGui::Begin("Folder", &m_isOpen, ImGuiWindowFlags_NoCollapse))
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
		ImGui::PopStyleColor();
	}
}