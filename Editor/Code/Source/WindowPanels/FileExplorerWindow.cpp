#include "WindowPanels/FileExplorerWindow.hpp"

#include "imgui.h"

void FileExplorerWindow::Draw()
{
    // ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
    ImGui::SetNextWindowSize(ImVec2(1920.f, 600.f), ImGuiCond_FirstUseEver);

    if (p_isOpen)
    {
        ImGui::Begin(p_windowIdentifier.c_str(), &p_isOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);

        if (m_currentDirectory != std::filesystem::path(s_AssetPath))
        {
            if (ImGui::Button("<"))
            {
                m_currentDirectory = m_currentDirectory.parent_path();
            }
        }

        for (auto& directoryEntry : std::filesystem::directory_iterator(m_currentDirectory))
        {
            const auto& path = directoryEntry.path();
            auto relativePath = std::filesystem::relative(path, s_AssetPath);
            std::string filenameString = relativePath.filename().string();
            if (directoryEntry.is_directory())
            {
                if (ImGui::Button(filenameString.c_str()))
                {
                    m_currentDirectory /= directoryEntry.path().filename();
                }
            } else
            {
                ImGui::Button(filenameString.c_str());
            }
        }
        ImGui::PopStyleColor();
        ImGui::End();
    }
}
