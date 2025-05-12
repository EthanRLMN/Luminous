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

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    static_cast<void>(window); static_cast<void>(scancode);


    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        if (key == GLFW_KEY_N && (mods & GLFW_MOD_CONTROL))
            g_newFile = true;
        if (key == GLFW_KEY_O && (mods & GLFW_MOD_CONTROL))
            g_openFile = true;
        if (key == GLFW_KEY_S && (mods & GLFW_MOD_CONTROL) && !(mods & GLFW_MOD_ALT))
            g_saveFile = true;
        if (key == GLFW_KEY_S && (mods & GLFW_MOD_CONTROL) && (mods & GLFW_MOD_ALT))
            g_saveAs = true;

        if (key == GLFW_KEY_B && (mods & GLFW_MOD_CONTROL) && !(mods & GLFW_MOD_ALT))
            g_build = true;
        if (key == GLFW_KEY_B && (mods & GLFW_MOD_CONTROL) && (mods & GLFW_MOD_ALT))
            g_buildRun = true;

        if (key == GLFW_KEY_Z && (mods & GLFW_MOD_CONTROL))
            g_undo = true;
        if (key == GLFW_KEY_Y && (mods & GLFW_MOD_CONTROL))
            g_redo = true;

        if (key == GLFW_KEY_X && (mods & GLFW_MOD_CONTROL))
            g_cut = true;
        if (key == GLFW_KEY_C && (mods & GLFW_MOD_CONTROL))
            g_copy = true;
        if (key == GLFW_KEY_V && (mods & GLFW_MOD_CONTROL))
            g_paste = true;
        if (key == GLFW_KEY_D && (mods & GLFW_MOD_CONTROL))
            g_duplicate = true;
        if (key == GLFW_KEY_DELETE)
            g_delete = true;
    }
}

void SetupKeyCallback(GLFWwindow* window)
{
    glfwSetKeyCallback(window, KeyCallback);
}

void MainPanel::Render()
{
    if (g_newFile)
    {
        g_newFile = false;
    }
    if (g_openFile)
    {
        g_openFile = false;
    }
    if (g_saveFile)
    {
        g_saveFile = false;
    }
    if (g_saveAs)
    {
        g_saveAs = false;
    }
    if (g_build)
    {
        g_build = false;
    }
    if (g_buildRun)
    {
        g_buildRun = false;
    }

    if (g_undo)
    {
        g_undo = false;
    }
    if (g_redo)
    {
        g_redo = false;
    }
    if (g_cut)
    {
        g_cut = false;
    }
    if (g_copy)
    {
        g_copy = false;
    }
    if (g_paste)
    {
        g_paste = false;
    }
    if (g_duplicate)
    {
        g_duplicate = false;
    }
    if (g_delete)
    {
        p_editor->GetEngine()->GetEntityManager()->RemoveEntity(p_isEntitySelected);
        g_delete = false;
    }

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
