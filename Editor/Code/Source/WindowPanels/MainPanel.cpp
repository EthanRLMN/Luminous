#include "GLFW/glfw3.h"

#include "WindowPanels/MainPanel.hpp"
#include "Editor.hpp"
#include "imgui.h"
#include "stb_image.h"
#include "windows.h"

bool g_newFile = false;
bool g_openFile = false;
bool g_saveFile = false;
bool g_saveAs = false;
bool g_build = false;
bool g_buildRun = false;

bool g_undo = false;
bool g_redo = false;
bool g_cut = false;
bool g_copy = false;
bool g_paste = false;
bool g_duplicate = false;
bool g_delete = false;


void MainPanel::Render()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("New Project", "CTRL + N"))
            {
                g_newFile = true;
            }
            if(ImGui::MenuItem("Open Project...", "CTRL + O"))
            {
                g_openFile = true;
            }

            ImGui::Separator();
            if(ImGui::MenuItem("Save All", "CTRL + S"))
            {
                g_saveFile = true;
            }
            if(ImGui::MenuItem("Save All As...", "CTRL + ALT + S"))
            {
                g_saveAs = true;
            }

            ImGui::Separator();
            if(ImGui::MenuItem("Build Project", "CTRL + B"))
            {
                g_build = true;
            }
            if(ImGui::MenuItem("Build Project and Run", "CTRL + ALT + B"))
            {
                g_buildRun = true;
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
                g_undo = true;
            }
            if (ImGui::MenuItem("Redo", "CTRL + Y"))
            {
                g_redo = true;
            }

            ImGui::Separator();
            if(ImGui::MenuItem("Cut", "CTRL + X"))
            {
                g_cut = true;
            }
            if(ImGui::MenuItem("Copy", "CTRL + C"))
            {
                g_copy = true;
            }
            if(ImGui::MenuItem("Paste", "CTRL + V"))
            {
                g_paste = true;
            }
            if(ImGui::MenuItem("Duplicate", "CTRL + D"))
            {
                g_duplicate = true;
            }
            if(ImGui::MenuItem("Delete", "DEL"))
            {
                g_delete = true;
            }

            ImGui::Separator();
            ImGui::MenuItem("Settings");

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
        ImGui::MenuItem("About");
        ImGui::Separator();
        if(ImGui::MenuItem("Luminous Engine Documentation"))
        {
            std::string l_url = "https://docs.google.com/document/d/19qMj7aVNyUmKaU75l3vGquVxbhHGDizC_6ZDZihrUx8/edit?pli=1&tab=t.0#heading=h.gb8ifdy1ueeo";
            ShellExecuteA(NULL, "open", l_url.c_str(), NULL, NULL, SW_SHOWNORMAL);
        }
        if (ImGui::MenuItem("Credits"))
        {
            std::string l_url = "https://docs.google.com/document/d/19qMj7aVNyUmKaU75l3vGquVxbhHGDizC_6ZDZihrUx8/edit?pli=1&tab=t.0#heading=h.gb8ifdy1ueeo";
            ShellExecuteA(NULL, "open", l_url.c_str(), NULL, NULL, SW_SHOWNORMAL);
        }
        ImGui::MenuItem("Report a Bug");
        ImGui::EndMenu();
    }
}
