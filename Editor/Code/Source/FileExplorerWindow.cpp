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

        for (auto& p : std::filesystem::directory_iterator(m_currentDirectory))
        {
            std::string path = p.path().string();
            if (p.is_directory())
            {
                if (ImGui::Button(path.c_str()))
                {
                }
            }
        }

        ImGui::PopStyleColor();
        ImGui::End();
    }
}
