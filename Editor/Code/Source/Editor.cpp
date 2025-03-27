#include "imgui/imgui.h"

#include "Engine.hpp"
#include "Core/GLFW/GLFWWindow.hpp"

void Destroy()
{
    /*ImGui_ImplVulkan_Shutdown();
    ImGui_ImplGlfw_Shutdown();*/
    //ImGui::DestroyContext();
}

int main()
{
    const Engine l_Engine;
    l_Engine.Run();

    IMGUI_CHECKVERSION();

    //ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO();
    /*ImGui_ImplGlfw_InitForVulkan(l_application->GetWindow()->CastVulkan()->GetGLFWWindow(), true);*/

    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    /*ImGui_ImplVulkan_InitInfo l_vulkanInfo{};
    l_vulkanInfo.Instance = VK_NULL_HANDLE;

    ImGui_ImplVulkan_Init(&l_vulkanInfo);*/

    //ImGui::ShowDemoWindow(); // Show demo window! :)

    while (!l_Engine.GetWindow()->ShouldClose())
    {
        // Poll events before doing anything else
        /*glfwPollEvents();

        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplGlfw_NewFrame();*/
        //ImGui::NewFrame();

        // Handle rendering
        //ImGui::Render();
        //ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), l_application.GetCo);
    }

    //Destroy();
    return 0;
}