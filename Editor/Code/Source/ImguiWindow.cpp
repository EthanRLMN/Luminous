#include "ImguiWindow.hpp"
#include "GLFW/glfw3.h"

#include "Core/GLFW/GLFWWindow.hpp"
#include "Engine.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"

void ImguiWindow::Create()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplGlfw_InitForVulkan(GLFWWindow.GetGLFWWindow(), true);
}

void ImguiWindow::Shutdown()
{
	ImGui_ImplVulkan_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImguiWindow::BeginRender()
{
	ImGui_ImplVulkan_NewFrame();
	ImGui::NewFrame();
}

void ImguiWindow::EndRender()
{
	ImGui::Render();
	ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(),Engine.GetCommandBuffer());
}

bool ImguiWindow::WantCaptureMouse()
{
	return ImGui::GetIO().WantCaptureMouse;
}

bool ImguiWindow::WantCaptureKeyboard()
{
	return ImGui::GetIO().WantCaptureKeyboard;
}