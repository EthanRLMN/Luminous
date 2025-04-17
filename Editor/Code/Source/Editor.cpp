#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"

#include "Editor.hpp"
#include "EditorStyle.hpp"

#include "Interface/IWindowPanel.hpp"

#include "Core/GLFW/GLFWWindow.hpp"

#include "Rendering/Vulkan/VulkanCommandBuffer.hpp"
#include "Rendering/Vulkan/VulkanCommandPool.hpp"
#include "Rendering/Vulkan/VulkanDescriptor.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanInstance.hpp"
#include "Rendering/Vulkan/VulkanRenderPass.hpp"
#include "Rendering/Vulkan/VulkanRenderer.hpp"

#include "WindowPanels/FileExplorerWindow.hpp"
#include "WindowPanels/HierarchyWindow.hpp"
#include "WindowPanels/InspectorWindow.hpp"
#include "WindowPanels/MainWindow.hpp"
#include "WindowPanels/ViewportWindow.hpp"

void Editor::Destroy()
{
    m_engine->GetDevice()->CastVulkan()->WaitIdle();
    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    m_engine->Destroy();
    delete m_engine;
    m_engine = nullptr;
}

void Editor::Init()
{
    m_engine = new Engine();
    m_engine->Init();
    SetupImGui();
    CreateWindows();
}

void Editor::SetupImGui() const
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    EditorStyle::SetupImGuiStyle();
    ImGuiIO& l_io = ImGui::GetIO(); static_cast<void>(l_io);
    l_io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable | ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_IsSRGB | ImGuiDockNodeFlags_NoWindowMenuButton;
    l_io.ConfigViewportsNoTaskBarIcon = false;
    l_io.ConfigViewportsNoAutoMerge = false;
    l_io.ConfigDockingAlwaysTabBar = true;
    l_io.Fonts->AddFontFromFileTTF("Editor/Assets/Fonts/Roboto-Bold.ttf", 18.0f, nullptr, l_io.Fonts->GetGlyphRangesDefault());

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
    l_initInfo.MSAASamples = m_engine->GetDevice()->CastVulkan()->GetMSAASamples();

    ImGui_ImplVulkan_Init(&l_initInfo);
    ImGui_ImplVulkan_CreateFontsTexture();

    m_engine->GetEditorCommandPool()->CastVulkan()->Create(m_engine->GetDevice(), m_engine->GetSurface());
    m_engine->GetEditorRenderPass()->CastVulkan()->CreateEditorPass(m_engine->GetSwapChain(), m_engine->GetDevice());
}

void Editor::Update()
{
    while (m_engine->IsRunning())
    {
        m_engine->Update();

        Render();
    }
}

void Editor::Render() const
{
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    DrawWindows();

    ImGui::Render();

    VulkanRenderer::RegisterGuiCallback([&] { ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), m_engine->GetCommandBuffer()->CastVulkan()->GetCommandBuffers()[m_engine->GetRenderingDraw()->CastVulkan()->GetCurrentFrame()]); });

    const ImGuiIO& l_io = ImGui::GetIO();
    if (l_io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

void Editor::CreateWindows()
{
    new MainWindow(this, "Editor");
    new ViewportWindow(this, "Viewport");
    new FileExplorerWindow(this, "File Explorer");
    new InspectorWindow(this, "Inspector");
    new HierarchyWindow(this, "Hierarchy");
}

void Editor::DrawWindows() const
{
    for (IWindowPanel* l_windowPanel : m_windows)
        l_windowPanel->Draw();
}

void Editor::DestroyWindows() const
{
    for (const IWindowPanel* l_windowPanel : m_windows)
        delete l_windowPanel;
}