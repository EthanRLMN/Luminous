#include "Application.hpp"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"
#include "Vector2.hpp"

void Destroy()
{
    ImGui::DestroyContext();

}

int main()
{
    const Application application;
    application.Run();

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    Maths::Vector2 test = Maths::Vector2{{5.f}, {13.f}};
    DEBUG_LOG_INFO("{}", test);

    // Setup Platform/Renderer backends
//    ImGui_ImplVulkan_InitInfo l_vulkanInfo{};
//    l_vulkanInfo.Instance = VK_NULL_HANDLE;

//    ImGui_ImplVulkan_Init(&l_vulkanInfo);
//    ImGui_ImplGlfw_InitForVulkan(application.s_Window.m_Window, false);

    ImGui::NewFrame();
    ImGui::ShowDemoWindow(); // Show demo window! :)

    /*while (!glfwWindowShouldClose())
    {
        // Poll events before doing anything else
        glfwPollEvents();

        // Render new vulkan frame then glfw frame then push it to imgui
//        ImGui_ImplVulkan_NewFrame();
//        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Handle rendering
        ImGui::Render();
        //ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData());
    }*/

    getchar();

    Destroy();
    return 0;
}