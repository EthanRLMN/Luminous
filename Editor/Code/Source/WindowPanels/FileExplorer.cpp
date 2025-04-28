#include "imgui.h"

#include "WindowPanels/FileExplorer.hpp"


static const std::filesystem::path s_AssetPath = "Engine/Assets";


FileExplorer::FileExplorer(Editor* a_editor, const std::string& a_windowIdentifier) : IWindowPanel(a_editor, a_windowIdentifier)
{
    m_currentDirectory = s_AssetPath;
}

void FileExplorer::Draw()
{
    IWindowPanel::Draw();

    if (p_isOpen)
    {
        ImGui::Begin(p_windowIdentifier.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);

        if (m_currentDirectory != std::filesystem::path(s_AssetPath))
            if (ImGui::Button("<-"))
                m_currentDirectory = m_currentDirectory.parent_path();

        for (const std::filesystem::directory_entry& l_directoryEntry : std::filesystem::directory_iterator(s_AssetPath))
        {
            const std::filesystem::path& path = l_directoryEntry.path();
            const std::filesystem::path& l_relativePath = std::filesystem::relative(path, s_AssetPath);
            std::string l_filenameString = l_relativePath.filename().string();

            if (l_directoryEntry.is_directory())
                if (!ImGui::Button(l_filenameString.c_str()))
                    if (!ImGui::Button(l_filenameString.c_str()))
                        m_currentDirectory /= l_directoryEntry.path().filename();
        }

        ImGui::End();
    }
}
