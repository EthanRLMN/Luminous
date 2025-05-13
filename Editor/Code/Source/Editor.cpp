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
#include "Rendering/Vulkan/VulkanRenderPassManager.hpp"
#include "Rendering/Vulkan/VulkanRenderer.hpp"
#include "WindowPanels/ConsolePanel.hpp"

#include "WindowPanels/FileExplorerPanel.hpp"
#include "WindowPanels/HierarchyPanel.hpp"
#include "WindowPanels/InspectorPanel.hpp"
#include "WindowPanels/MainPanel.hpp"
#include "WindowPanels/ViewportPanel.hpp"

Editor::~Editor()
{
    DestroyWindowPanels();
    Destroy();
}

void Editor::Destroy()
{
    if (m_engine)
    {
        for (IWindowPanel* window : m_windows)
            UnregisterWindow(window);

        m_engine->GetDevice()->CastVulkan()->WaitIdle();
        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

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
    CreateWindowPanels();
}

void Editor::SetupImGui() const
{
    ImGui::CreateContext();

    ImGuiIO& l_io = ImGui::GetIO(); static_cast<void>(l_io);
    l_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_IsSRGB | ImGuiDockNodeFlags_NoWindowMenuButton;
    l_io.ConfigViewportsNoTaskBarIcon = false;
    l_io.ConfigViewportsNoAutoMerge = false;
    l_io.ConfigDockingAlwaysTabBar = true;
    l_io.IniFilename = "Editor/Assets/EditorConfig.ini";

    l_io.Fonts->AddFontFromFileTTF("Editor/Assets/Fonts/Roboto-Bold.ttf", 18.0f, nullptr, l_io.Fonts->GetGlyphRangesDefault());

    EditorStyle::SetupImGuiStyle();

    ImGui_ImplGlfw_InitForVulkan(m_engine->GetWindow()->CastGLFW()->GetGLFWWindow(), true);

    ImGui_ImplVulkan_InitInfo l_initInfo{};
    l_initInfo.ApiVersion = VK_API_VERSION_1_4;
    l_initInfo.Instance = m_engine->GetInstance()->CastVulkan()->GetInstance();
    l_initInfo.Queue = m_engine->GetDevice()->CastVulkan()->GetGraphicsQueue();
    l_initInfo.DescriptorPool = m_engine->GetDescriptor()->CastVulkan()->GetImGUIDescriptorPool();
    l_initInfo.RenderPass = m_engine->GetRenderPassManager()->GetRenderPassAt(1)->CastVulkan()->GetRenderPass();
    l_initInfo.Device = m_engine->GetDevice()->CastVulkan()->GetDevice();
    l_initInfo.PhysicalDevice = m_engine->GetDevice()->CastVulkan()->GetPhysicalDevice();
    l_initInfo.MinImageCount = MAX_FRAMES_IN_FLIGHT;
    l_initInfo.ImageCount = MAX_FRAMES_IN_FLIGHT;

    ImGui_ImplVulkan_Init(&l_initInfo);
    ImGui_ImplVulkan_CreateFontsTexture();

    m_engine->GetEditorCommandPool()->CastVulkan()->Create(m_engine->GetDevice(), m_engine->GetSurface());
}

void Editor::Update()
{
    while (m_engine->IsRunning())
    {
        m_engine->Update();
        Render();

        if (ShouldExit())
        {
            Destroy();
            break;
        }
    }
}


void Editor::Render() const
{
    if (!m_engine || !m_engine->IsRunning())
        return;

    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Update the main docking space every frame
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

    RenderWindowPanels();

    ImGui::Render();

    // We need to re-register the callback every frame since it needs to get the current frame rendered
    VulkanRenderer::RegisterEditorRenderCallback([&] { ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), m_engine->GetCommandBuffer()->CastVulkan()->GetCommandBuffers()[m_engine->GetRenderer()->CastVulkan()->GetCurrentFrame()]); });

    const ImGuiIO& l_io = ImGui::GetIO();
    if (l_io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

void Editor::CreateWindowPanels()
{
    RegisterWindow(new MainPanel(this, "Editor"));
    RegisterWindow(new Viewport(this, "Viewport"));
    RegisterWindow(new FileExplorerPanel(this, "File Explorer"));

    auto inspector = new InspectorPanel(this, "Inspector");
    RegisterWindow(inspector);

    auto hierarchy = new HierarchyPanel(this, "Hierarchy");
    hierarchy->SetInspectorPanel(inspector);
    RegisterWindow(hierarchy);

    RegisterWindow(new ConsolePanel(this, "Console"));
}


void Editor::RenderWindowPanels() const
{
    if (!m_engine || !m_engine->IsRunning())
        return;

    for (IWindowPanel* l_windowPanel : m_windows)
    {
        if (l_windowPanel)
            l_windowPanel->Render();
    }
}

void Editor::DestroyWindowPanels()
{
    for (const IWindowPanel* l_panel : m_windows)
        delete l_panel;
    
    m_windows.clear();
}

void Editor::UnregisterWindow(IWindowPanel* a_windowPanel)
{
    std::erase(m_windows, a_windowPanel);
}
