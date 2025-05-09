#include "WindowPanels/ConsolePanel.hpp"

#include "imgui.h"



void ConsolePanel::Render()
{

    IWindowPanel::Render();

    if (p_isOpen)
    {
        ImGui::Begin(p_windowIdentifier.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);



        // Zone d'affichage des logs
        if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar)) {
            for (const auto& item : m_items) {
                ImGui::TextUnformatted(item.c_str());
            }
            ImGui::SetScrollHereY(1.0f); // scroll vers le bas
        }
        ImGui::EndChild();

        // Champ d'entrée
        ImGui::Separator();
        if (ImGui::InputText("Input", reinterpret_cast<char*>(&m_inputBuffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
            AddLog("> " + m_inputBuffer);
            m_inputBuffer.clear();
        }



        ImGui::PopStyleColor();
        ImGui::End();
    }
}

void ConsolePanel::AddLog(const std::string& a_log)
{
    m_items.push_back(a_log);
}
