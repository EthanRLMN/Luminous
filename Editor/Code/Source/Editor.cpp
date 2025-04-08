#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"

#include "Editor.hpp"

#include "Core/GLFW/GLFWWindow.hpp"
#include "Rendering/Vulkan/VulkanCommandBuffer.hpp"
#include "Rendering/Vulkan/VulkanDescriptor.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanInstance.hpp"
#include "Rendering/Vulkan/VulkanRenderPass.hpp"


void Editor::Destroy()
{
    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (m_engine)
    {
        delete m_engine;
        m_engine = nullptr;
    }
}

void Editor::Init()
{
    m_engine = new Engine();
    m_engine->Init();
    SetupImGui();
}

void Editor::SetupImGui() const
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& l_io = ImGui::GetIO();
    l_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    l_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplGlfw_InitForVulkan(m_engine->GetWindow()->CastGLFW()->GetGLFWWindow(), true);
    const uint32_t l_queueFamilyIndex = m_engine->GetDevice()->CastVulkan()->GetQueueFamilies(m_engine->GetDevice()->CastVulkan()->GetPhysicalDevice(), m_engine->GetSurface()->CastVulkan()->GetSurface()).graphicsFamily;

    ImGui_ImplVulkan_InitInfo l_initInfo{};
    l_initInfo.ApiVersion = VK_API_VERSION_1_3;
    l_initInfo.Instance = m_engine->GetInstance()->CastVulkan()->GetInstance();
    l_initInfo.PhysicalDevice = m_engine->GetDevice()->CastVulkan()->GetPhysicalDevice();
    l_initInfo.Device = m_engine->GetDevice()->CastVulkan()->GetDevice();
    l_initInfo.QueueFamily = l_queueFamilyIndex;
    l_initInfo.Queue = m_engine->GetDevice()->CastVulkan()->GetGraphicsQueue();
    l_initInfo.PipelineCache = nullptr;
    l_initInfo.DescriptorPool = m_engine->GetDescriptor()->CastVulkan()->GetImGUIDescriptorPool();
    l_initInfo.MinImageCount = 3;
    l_initInfo.ImageCount = 3;
    l_initInfo.Allocator = nullptr;
    l_initInfo.CheckVkResultFn = nullptr;
    l_initInfo.RenderPass = m_engine->GetRenderPass()->CastVulkan()->GetRenderPass();

    ImGui_ImplVulkan_Init(&l_initInfo);
    ImGui_ImplVulkan_CreateFontsTexture();

    IM_ASSERT(ImGui::GetDrawData() != nullptr);
    IM_ASSERT(ImGui::GetDrawData()->CmdListsCount > 0);
}

void Editor::Update() const
{
    while (m_engine->IsRunning())
    {
        m_engine->GetWindow()->PollEvents();

        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();
        DEBUG_LOG_VERBOSE("Test");

        ImGui::Render();
        ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), m_engine->GetCommandBuffer()->CastVulkan()->GetCommandBuffers()[0]);

        m_engine->Update();
    }
}
