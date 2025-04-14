#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"

#include "Editor.hpp"
#include "MainWindow.hpp"
#include "FoldersWindow.hpp"
#include "InspectorWindow.hpp"
#include "HierarchyWindow.hpp"

#include "Core/GLFW/GLFWWindow.hpp"
#include "Rendering/Vulkan/VulkanCommandBuffer.hpp"
#include "Rendering/Vulkan/VulkanCommandPool.hpp"
#include "Rendering/Vulkan/VulkanDescriptor.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanInstance.hpp"
#include "Rendering/Vulkan/VulkanRenderPass.hpp"
#include "Rendering/Vulkan/VulkanRenderer.hpp"


void Editor::Destroy()
{
    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (m_engine)
    {
        m_engine->Destroy();

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
    l_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_IsSRGB;
    l_io.ConfigDockingAlwaysTabBar = true;

    ImGui_ImplGlfw_InitForVulkan(m_engine->GetWindow()->CastGLFW()->GetGLFWWindow(), true);

    ImGui_ImplVulkan_InitInfo l_initInfo{};
    l_initInfo.ApiVersion = VK_API_VERSION_1_4;
    l_initInfo.Instance = m_engine->GetInstance()->CastVulkan()->GetInstance();
    l_initInfo.Queue = m_engine->GetDevice()->CastVulkan()->GetGraphicsQueue();
    l_initInfo.DescriptorPool = m_engine->GetDescriptor()->CastVulkan()->GetImGUIDescriptorPool();
    l_initInfo.RenderPass = m_engine->GetRenderPass()->CastVulkan()->GetRenderPass();
    l_initInfo.Device = m_engine->GetDevice()->CastVulkan()->GetDevice();
    l_initInfo.PhysicalDevice = m_engine->GetDevice()->CastVulkan()->GetPhysicalDevice();
    l_initInfo.MinImageCount = MAX_FRAMES_IN_FLIGHT;
    l_initInfo.ImageCount = MAX_FRAMES_IN_FLIGHT;
    l_initInfo.MSAASamples = VK_SAMPLE_COUNT_1_BIT;

    ImGui_ImplVulkan_Init(&l_initInfo);
    ImGui_ImplVulkan_CreateFontsTexture();

    m_engine->GetEditorCommandPool()->CastVulkan()->Create(m_engine->GetDevice(), m_engine->GetSurface());
    m_engine->GetEditorRenderPass()->CastVulkan()->CreateUIPass(m_engine->GetSwapChain(), m_engine->GetDevice());
}

void Editor::Update()
{

    while (m_engine->IsRunning())
    {
        m_engine->Update();

        ImGui_ImplVulkan_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        DrawWindows();

        Render();
        VulkanRenderer::RegisterGuiCallback([&] { ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), m_engine->GetCommandBuffer()->CastVulkan()->GetCommandBuffers()[m_engine->GetRenderingDraw()->CastVulkan()->GetCurrentFrame()]); });

        const ImGuiIO& l_io = ImGui::GetIO();
        if (l_io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
    }
}

void Editor::Render() const
{
    ImGui::Render();
}

void Editor::DrawWindows()
{
    MainWindow mainWindow;
    FoldersWindow foldersWindow;
    InspectorWindow inspectorWindow;
    HierarchyWindow hierarchyWindow;

    mainWindow.Draw();
    foldersWindow.Draw();
    inspectorWindow.Draw();
    hierarchyWindow.Draw();
}