#include <imgui.h>

#include "MainWindow.hpp"

#include "backends/imgui_impl_glfw.h"
#include "Rendering/Window.hpp"


void MainWindow::SetupImGUIContext(const Window a_window)
{
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForVulkan(a_window.m_Window, false);

    ImGui::NewFrame();
    ImGui::ShowDemoWindow(); // Show demo window! :)
}
