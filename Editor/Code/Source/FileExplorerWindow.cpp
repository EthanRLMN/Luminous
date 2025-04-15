#include "FileExplorerWindow.hpp"

#include "imgui.h"

#include <filesystem>

void FileExplorerWindow::Draw()
{
    ImGui::SetNextWindowSize({ 1920, 215 }, ImGuiCond_FirstUseEver);
    
    const char* s_AssetsDirectory = "assets";

    if (p_isOpen)
    {
        ImGui::Begin(p_windowIdentifier.c_str(), &p_isOpen, ImGuiWindowFlags_NoCollapse);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);

        /* for (auto& p : std::filesystem::directory_iterator(s_AssetsDirectory))
        {
            std::string path = p.path().string();
            ImGui::Text("%s", path.c_str());
        }*/

        ImGui::PopStyleColor();
        ImGui::End();
    }
}
