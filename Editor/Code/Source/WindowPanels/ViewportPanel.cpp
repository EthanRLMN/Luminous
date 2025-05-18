#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

#include "WindowPanels/ViewportPanel.hpp"

#include "Rendering/Vulkan/VulkanSwapChain.hpp"
#include "Rendering/Vulkan/VulkanTexture.hpp"
#include "ResourceManager/ResourceManager.hpp"

#include <windows.h>
#include <filesystem>
#include <direct.h>

static const std::filesystem::path s_IconPath = "Editor/Assets/Icons/";

void Viewport::Render()
{
    IWindowPanel::Render();

    ImGui::Begin(p_windowIdentifier.c_str(), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground);
    
    ImVec2 avail = ImGui::GetContentRegionAvail();
    float buttonWidth = 40.f;
    float buttonHeight = 40.f;
    ImVec2 buttonSize(buttonWidth, buttonHeight);

    if (ImGui::ImageButton("Move",m_iconMoveID, buttonSize)) 
    {
    
    }
    ImGui::SameLine();
    if (ImGui::ImageButton("Rotate",m_iconRotateID, buttonSize)) 
    {
    
    }
    ImGui::SameLine();
    if (ImGui::ImageButton("Resize", m_iconResizeID, buttonSize)) 
    {
    
    }

    ImGui::SameLine(0, 0.4f * avail.x);

    if (ImGui::ImageButton("Play", m_iconPlayID, buttonSize)) 
    {

        std::array<char, 1024> l_buffer{};
        if (_getcwd(l_buffer.data(), 1024) != nullptr)
            DEBUG_LOG_INFO("Current working directory: {}\n", l_buffer.data());

        const char* exePath = "L_RUNTIME.exe";

        if (std::filesystem::exists(exePath))
        {

            /*
            STARTUPINFOA si = { sizeof(STARTUPINFOA) };
            PROCESS_INFORMATION pi;

            if (!CreateProcessA(exePath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
            {
                MessageBoxA(NULL, "Can't launch runtime", "Error", MB_OK | MB_ICONERROR);
                return;
            }

            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);*/
            ShellExecute(NULL, "open", exePath, NULL, NULL, SW_SHOWDEFAULT);
        }

        
        
    }
    ImGui::SameLine();
    if (ImGui::ImageButton("Stop", m_iconStopID, buttonSize)) 
    {
    
    }

    if (p_editor->GetEngine()->GetRenderer()->CastVulkan()->m_recreateDsets)
    {
        p_editor->GetEngine()->GetRenderer()->CastVulkan()->m_recreateDsets = false;
        dSets = reinterpret_cast<ImTextureID>(ImGui_ImplVulkan_AddTexture(ResourceManager::GetInstance().GetStandardSampler(), p_editor->GetEngine()->GetRenderer()->CastVulkan()->GetViewportImageView(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL));
    };


    VkExtent2D l_extent = p_editor->GetEngine()->GetSwapChain()->CastVulkan()->GetSwapChainExtent();

    float l_texWidth = static_cast<float>(l_extent.width);
    float l_texHeight = static_cast<float>(l_extent.height);
    float l_aspectRatio = l_texWidth / l_texHeight;

    ImVec2 l_avail = ImGui::GetContentRegionAvail();
    float l_fitWidth = l_avail.x;
    float l_fitHeight = l_fitWidth / l_aspectRatio;
    
    if (l_fitHeight > l_avail.y)
    {
        l_fitHeight = l_avail.y;
        l_fitWidth = l_fitHeight * l_aspectRatio;
    }

    const ImVec2 l_imageSize(l_fitWidth, l_fitHeight);

    const ImVec2 l_screenPos = ImGui::GetCursorScreenPos();
    const float l_offsetX = (l_avail.x - l_imageSize.x) * 0.5f;
    const float l_offsetY = (l_avail.y - l_imageSize.y) * 0.5f;

    ImGui::SetCursorScreenPos(ImVec2(l_screenPos.x + l_offsetX, l_screenPos.y + l_offsetY));


    ImGui::Image(dSets, l_imageSize);
    ImGui::End();
}

void Viewport::InitIcons()
{
    Engine* engine = p_editor->GetEngine();
    auto* device = engine->GetDevice();

    m_iconMove = LoadTexture(engine, (s_IconPath / "MoveIcon.png").string());
    m_iconRotate = LoadTexture(engine, (s_IconPath / "RotateIcon.png").string());
    m_iconResize = LoadTexture(engine, (s_IconPath / "ResizeIcon.png").string());
    m_iconPlay = LoadTexture(engine, (s_IconPath / "PlayIcon.png").string());
    m_iconStop = LoadTexture(engine, (s_IconPath / "StopIcon.png").string());

    auto loadImg = [&](std::shared_ptr<ITexture>& tex, ImTextureID& id)
    {
        tex->CastVulkan()->CreateTextureImageView(device);
        id = reinterpret_cast<ImTextureID>(ImGui_ImplVulkan_AddTexture(
                ResourceManager::GetInstance().GetStandardSampler(),
                tex->CastVulkan()->GetTextureImageView(),
                VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL));
    };

    loadImg(m_iconMove, m_iconMoveID);
    loadImg(m_iconRotate, m_iconRotateID);
    loadImg(m_iconResize, m_iconResizeID);
    loadImg(m_iconPlay, m_iconPlayID);
    loadImg(m_iconStop, m_iconStopID);
}

std::shared_ptr<ITexture> Viewport::LoadTexture(const Engine* engine, const std::string& path)
{
    IResourceParams params{};
    params.m_device = engine->GetDevice();
    params.m_commandPool = engine->GetCommandPool();
    params.m_texturePath = path;

    auto texture = std::make_shared<VulkanTexture>();
    texture->CreateTextureImage(params.m_device, params.m_commandPool, params.m_texturePath);
    return texture;
}
