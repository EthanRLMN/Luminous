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
            if(ImGui::MenuItem("New Project", "CTRL + N"))
            {

            }
            if(ImGui::MenuItem("Open Project...", "CTRL + O"))
            {

            }

            ImGui::Separator();
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

        if (ImGui::BeginMenu("Edit"))
        {
            if(ImGui::MenuItem("Undo", "CTRL + Z"))
            {

            }
            if (ImGui::MenuItem("Redo", "CTRL + Y"))
            {

            }

            ImGui::Separator();
            if(ImGui::MenuItem("Cut", "CTRL + X"))
            {

            }
            if(ImGui::MenuItem("Copy", "CTRL + C"))
            {

            }
            if(ImGui::MenuItem("Paste", "CTRL + V"))
            {

            }
            if(ImGui::MenuItem("Duplicate", "CTRL + D"))
            {

            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window"))
        {
            if(ImGui::MenuItem("Scene"))
            {

            }
            if(ImGui::MenuItem("Game"))
            {

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
