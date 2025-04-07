#include "ImguiWindow.hpp"

#include "Engine.hpp"
#include "Core/GLFW/GLFWWindow.hpp"
#include "Rendering/Vulkan/VulkanCommandBuffer.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"

void ImguiWindow::Create(const GLFWWindow* a_glfwWindow)
{
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

void ImguiWindow::EndRender(const Engine* a_engine)
{
	ImGui::Render();
	ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), a_engine->GetCommandBuffer()->CastVulkan()->GetCommandBuffers()[1]);
}

bool ImguiWindow::WantCaptureMouse()
{
	return ImGui::GetIO().WantCaptureMouse;
}

bool ImguiWindow::WantCaptureKeyboard()
{
	return ImGui::GetIO().WantCaptureKeyboard;
}