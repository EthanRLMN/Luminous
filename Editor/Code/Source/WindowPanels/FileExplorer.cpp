#include "WindowPanels/FileExplorer.hpp"

#include "imgui.h"

static const std::filesystem::path s_AssetPath = "Engine/Assets";


FileExplorer::FileExplorer(Editor* a_editor, const std::string& a_windowIdentifier) : IWindowPanel(a_editor, a_windowIdentifier)
{
    m_currentDirectory = s_AssetPath;
}

void FileExplorer::Draw()
{
    if (p_isOpen)
    {
        ImGui::SetNextWindowPos(ImVec2(5, 960), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(1935, 405), ImGuiCond_FirstUseEver);

        ImGui::Begin(p_windowIdentifier.c_str(), &p_isOpen, ImGuiWindowFlags_NoCollapse);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);

        if (m_currentDirectory != std::filesystem::path(s_AssetPath))
            if (ImGui::Button("<-"))
                m_currentDirectory = m_currentDirectory.parent_path();

        for (const std::filesystem::directory_entry& l_directoryEntry : std::filesystem::directory_iterator(s_AssetPath))
        {
            const auto& path = l_directoryEntry.path();
            const std::filesystem::path l_relativePath = std::filesystem::relative(path, s_AssetPath);
            std::string l_filenameString = l_relativePath.filename().string();

            if (l_directoryEntry.is_directory())
                if (ImGui::Button(l_filenameString.c_str()))
                    m_currentDirectory /= l_directoryEntry.path().filename();
            else
                if (ImGui::Button(l_filenameString.c_str()))
                {

                }
        }

        ImGui::PopStyleColor();
        ImGui::End();
    }
}
