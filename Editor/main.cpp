#include "Application.hpp"
#include "imgui.h"
#include "MainWindow.hpp"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"
#include "Rendering/API/Vulkan/VulkanWindow.hpp"

void MainWindow::Shutdown()
{
	//ImGui_ImplVulkan_Shutdown();
	//ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void MainWindow::Create()
{
	IMGUI_CHECKVERSION();

	ImGui::CreateContext();

	Application *application = new Application();
	GLFWwindow* window = application->GetWindow()->CastVulkan()->GetGLFWWindow();
	ImGui_ImplGlfw_InitForVulkan(window, true);
}

int main()
{
	const Application l_application;
	l_application.Run();

	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	/*ImGui_ImplVulkan_InitInfo l_vulkanInfo{};
	l_vulkanInfo.Instance = VK_NULL_HANDLE;*/

	//ImGui_ImplVulkan_Init(&l_vulkanInfo);

	ImGui::ShowDemoWindow(); // Show demo window! :)
	//mainWindow.Open();

	while (!l_application.GetWindow()->ShouldClose())
	{
		// Poll events before doing anything else
		glfwPollEvents();

		/*ImGui_ImplVulkan_NewFrame();
		ImGui_ImplGlfw_NewFrame();*/
		ImGui::NewFrame();

		// Handle rendering
		ImGui::Render();
		//ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), l_application.GetCo);
		//mainWindow.Draw();
	}

	//Destroy();
	return 0;
}