#include "WindowPanels/MainPanel.hpp"
#include "Editor.hpp"
#include "glfw/glfw3.h"
#include "imgui.h"
#include "stb_image.h"

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
        g_delete = false;
    }

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("New Project", "CTRL + N");
            ImGui::MenuItem("Open Project...", "CTRL + O");

            if (ImGui::BeginMenu("Open Recent Project"))
            {
                ImGui::MenuItem("Project1");
                ImGui::MenuItem("Project2");
                ImGui::EndMenu();
            }

            ImGui::Separator();
            ImGui::MenuItem("Save All", "CTRL + S");
            ImGui::MenuItem("Save All As...", "CTRL + ALT + S");

            ImGui::Separator();
            ImGui::MenuItem("Build Project", "CTRL + B");
            ImGui::MenuItem("Build Project and Run", "CTRL + ALT + B");

            ImGui::Separator();
            ImGui::MenuItem("Exit");

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            ImGui::MenuItem("Undo", "CTRL + Z");
            ImGui::MenuItem("Redo", "CTRL + Y");

            ImGui::Separator();
            ImGui::MenuItem("Cut", "CTRL + X");
            ImGui::MenuItem("Copy", "CTRL + C");
            ImGui::MenuItem("Paste", "CTRL + V");
            ImGui::MenuItem("Duplicate", "CTRL + D");
            ImGui::MenuItem("Delete", "DEL");

            ImGui::Separator();
            ImGui::MenuItem("Settings");

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window"))
        {
            ImGui::MenuItem("Console");
            ImGui::MenuItem("Scene");
            ImGui::MenuItem("Game");
            ImGui::EndMenu();
        }

        HelpContextMenu();

        ImGui::EndMainMenuBar();
    }

    ImGui::SetNextWindowDockID(ImGui::GetID("Scene Options"), ImGuiCond_FirstUseEver);
    ImGui::Begin("Scene Options", nullptr,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    if (ImGui::Button("Move")) {}
    ImGui::SameLine();
    if (ImGui::Button("Rotate")) {}
    ImGui::SameLine();
    if (ImGui::Button("Resize")) {}

    ImGui::SameLine(0, 100 * ImGui::GetStyle().ItemSpacing.x);
    if (ImGui::Button("Play")) {}
    ImGui::SameLine();
    if (ImGui::Button("Stop")) {}

    ImGui::End();
}

void MainPanel::HelpContextMenu()
{
    if (ImGui::BeginMenu("Help"))
    {
        ImGui::MenuItem("About");
        ImGui::Separator();
        ImGui::MenuItem("Luminous Engine Documentation");
        ImGui::MenuItem("Credits");
        ImGui::MenuItem("Report a Bug");
        ImGui::EndMenu();
    }
}
