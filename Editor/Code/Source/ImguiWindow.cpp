#include "ImguiWindow.hpp"

#include "Application.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"

void ImguiWindow::Shutdown()
{
	ImGui_ImplVulkan_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImguiWindow::Create()
{
	IMGUI_CHECKVERSION();

	ImGui::CreateContext();

	auto* window = Application::GetWindow();
	ImGui_ImplGlfw_InitForVulkan(window->CastVulkan()->GetGLFWWindow(), true);
}

void ImguiWindow::BeginRender()
{
	ImGui_ImplVulkan_NewFrame();
	ImGui::NewFrame();
}

void ImguiWindow::EndRender()
{
	ImGui::Render();
	ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData());
}