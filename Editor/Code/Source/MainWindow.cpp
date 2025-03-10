#include "MainWindow.hpp"

#include <imgui.h>

void MainWindow::SetupImGUIContext()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(YOUR_HWND);
    ImGui_ImplDX11_Init(YOUR_D3D_DEVICE, YOUR_D3D_DEVICE_CONTEXT);
}
