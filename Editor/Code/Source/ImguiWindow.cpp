#include "ImguiWindow.hpp"

#include "Application.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"
#include "backends/imgui_impl_sdl2.h"


void ImguiWindow::Shutdown()
{
	ImGui_ImplVulkan_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void ImguiWindow::Create()
{
	IMGUI_CHECKVERSION();

	ImGui::CreateContext();

	auto* window = Application::GetWindow();
	ImGui_ImplGlfw_InitForVulkan(window->CastVulkan()->GetGLFWWindow(), true);
	ImGui_ImplSDL2_InitForVulkan(window.GetSDLWindow(), window.GetGLContext());
}

void ImguiWindow::BeginRender()
{
	ImGui_ImplVulkan_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
}

void ImguiWindow::EndRender()
{
	ImGui::Render();
	ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData());
}