#include <vulkan/vulkan.h>
#include <iostream>

#include "Editor.hpp"

GLFWWindow glfwWindow;
VulkanInstance vulkanInstance;

Editor::~Editor()
{
    if (m_engine)
    {
        delete m_engine;
        m_engine = nullptr;
    }
}

void Editor::InitEditor()
{
    m_engine = new Engine();
    m_engine->Run();
}

void Editor::SetupImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplGlfw_InitForVulkan(glfwWindow.GetGLFWWindow(), true);

    ImGui_ImplVulkan_InitInfo init_info = {};
    init_info.Instance = vulkanInstance.GetInstance();
    init_info.PhysicalDevice = VK_NULL_HANDLE;
    init_info.Device = VK_NULL_HANDLE;
    init_info.QueueFamily = 0;
    init_info.Queue = VK_NULL_HANDLE;
    init_info.PipelineCache = VK_NULL_HANDLE;
    init_info.DescriptorPool = VK_NULL_HANDLE;
    init_info.Allocator = nullptr;
    init_info.CheckVkResultFn = nullptr;

    ImGui_ImplVulkan_Init(&init_info);
}

int Editor::main()
{
    GLFWwindow* window = glfwWindow.Initialize("Luminous", 1920, 1080);

    SetupImGui();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Render();

        glfwSwapBuffers(window);
    }

    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwWindow.Destroy();

    return 0;
}
