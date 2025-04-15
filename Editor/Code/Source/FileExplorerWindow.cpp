#include "FileExplorerWindow.hpp"

#include "imgui.h"


const char* s_AssetsDirectory = "Engine/Assets";
    
void FileExplorerWindow::ContentBrowserPanel() 
{
    m_currentDirectory = s_AssetsDirectory;
}

void FileExplorerWindow::Draw()
{
    ImGui::SetNextWindowSize({ 1920, 215 }, ImGuiCond_FirstUseEver);
    

    if (p_isOpen)
    {
        ImGui::Begin(p_windowIdentifier.c_str(), &p_isOpen, ImGuiWindowFlags_NoCollapse);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);

        if (m_currentDirectory != std::filesystem::path(s_AssetsDirectory))
        {
            if (ImGui::Button("<-"))
            {
                m_currentDirectory = m_currentDirectory.parent_path();
            }
        }

        for (auto& p : std::filesystem::directory_iterator(s_AssetsDirectory))
        {
            std::string path = p.path().string();
            if (p.is_directory())
            {
                if (ImGui::Button(path.c_str()))
                {
                    m_currentDirectory /= p.path().filename();
                }
            }
        }

        ImGui::PopStyleColor();
        ImGui::End();
    }
}
