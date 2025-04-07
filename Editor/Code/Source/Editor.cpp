#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"

#include "Editor.hpp"
#include "ImguiWindow.hpp"

#include "Core/GLFW/GLFWWindow.hpp"
#include "Rendering/Vulkan/VulkanDescriptor.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanInstance.hpp"
#include "Rendering/Vulkan/VulkanRenderPass.hpp"


void Editor::Destroy()
{
    if (m_engine)
    {
        delete m_engine;
        m_engine = nullptr;
    }
}

void Editor::Init()
{
    m_engine = new Engine();
    m_imguiWindow = new ImguiWindow();
}

void Editor::SetupImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& l_io = ImGui::GetIO();
    l_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    l_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplGlfw_InitForVulkan(m_engine->GetWindow()->CastGLFW()->GetGLFWWindow(), true);

    //TODO Change api version
    ImGui_ImplVulkan_InitInfo l_initInfo{ };
    l_initInfo.ApiVersion = VK_API_VERSION_1_4;
    l_initInfo.Instance = m_engine->GetInstance()->CastVulkan()->GetInstance();
    l_initInfo.PhysicalDevice = m_engine->GetDevice()->CastVulkan()->GetPhysicalDevice();
    l_initInfo.Device = m_engine->GetDevice()->CastVulkan()->GetDevice();
    l_initInfo.QueueFamily = 0;
    l_initInfo.Queue = m_engine->GetDevice()->CastVulkan()->GetGraphicsQueue();
    l_initInfo.PipelineCache = nullptr;
    l_initInfo.DescriptorPool = m_engine->GetDescriptor()->CastVulkan()->GetDescriptorPool();
    l_initInfo.MinImageCount = 3;
    l_initInfo.ImageCount = 3;
    l_initInfo.Allocator = nullptr;
    l_initInfo.CheckVkResultFn = nullptr;
    l_initInfo.RenderPass = m_engine->GetRenderPass()->CastVulkan()->GetRenderPass();

    m_imguiWindow->Create(m_engine->GetWindow()->CastGLFW());

    ImGui_ImplVulkan_Init(&l_initInfo);
}

void Editor::Launch()
{
    SetupImGui();

    while (!m_engine->GetWindow()->ShouldClose())
    {
        glfwPollEvents();

        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Render();

        glfwSwapBuffers(m_engine->GetWindow()->CastGLFW()->GetGLFWWindow());
    }

    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
