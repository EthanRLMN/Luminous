#include "GLFW/glfw3.h"

#include "WindowPanels/MainPanel.hpp"
#include "Editor.hpp"
#include "imgui.h"
#include "stb_image.h"
#include "windows.h"

void MainPanel::Render()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("Save Scene", "CTRL + S"))
            {
                p_editor->GetEngine()->GetScene()->SaveScene(m_scenePath, *p_editor->GetEngine()->GetEntityManager());
            }

            if (ImGui::MenuItem("Load Scene", "CTRL + L"))
            {
                p_editor->GetEngine()->GetScene()->LoadScene(m_scenePath, *p_editor->GetEngine()->GetEntityManager());
            }

            ImGui::Separator();
            if(ImGui::MenuItem("Build Project", "CTRL + B"))
            {
                
            }

            ImGui::Separator();
            if(ImGui::MenuItem("Exit"))
            {
                p_editor->RequestExit();
            }
            ImGui::EndMenu();
        }
        HelpContextMenu();

        ImGui::EndMainMenuBar();
    }
}


void MainPanel::HelpContextMenu()
{
    if (ImGui::BeginMenu("Help"))
    {
        if(ImGui::MenuItem("Luminous Engine Documentation"))
        {
            std::string l_url = "https://docs.google.com/document/d/19qMj7aVNyUmKaU75l3vGquVxbhHGDizC_6ZDZihrUx8/edit?pli=1&tab=t.0#heading=h.gb8ifdy1ueeo";
            ShellExecuteA(NULL, "open", l_url.c_str(), NULL, NULL, SW_SHOWNORMAL);
        }
        ImGui::EndMenu();
    }
}


bool MainPanel::RunCommand(const std::string& a_cmd)
{
#ifdef _WIN32
    std::string l_fullCmd = "cmd /C " + a_cmd;
#else
    std::string l_fullCmd = a_cmd;
#endif
    return std::system(l_fullCmd.c_str()) == 0;
}