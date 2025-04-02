#include "InspectorWindow.hpp"

void InspectorWindow::Draw()
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);
	ImGui::SetNextWindowSize({ 1920, 1080 }, ImGuiCond_FirstUseEver);

	if (m_isOpen && ImGui::Begin("Inspector", &m_isOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar))
	{
		
	}
	ImGui::End();
	ImGui::PopStyleColor();
}