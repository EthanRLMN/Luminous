#include "ImguiWindow.hpp"
#include "GLFW/glfw3.h"

#include "Application.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"

void ImguiWindow::Create()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplGlfw_InitForVulkan(VulkanWindow->GetGLFWWindow(), true);
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
	VkCommandBuffer commandBuffer = Application::GetVulkanCommandBuffer();
	ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandBuffer);
}

bool ImguiWindow::WantCaptureMouse()
{
	return ImGui::GetIO().WantCaptureMouse;
}

bool ImguiWindow::WantCaptureKeyboard()
{
	return ImGui::GetIO().WantCaptureKeyboard;
}