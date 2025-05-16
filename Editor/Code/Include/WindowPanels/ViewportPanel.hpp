#pragma once

#include "backends/imgui_impl_vulkan.h"

#include "Interface/IWindowPanel.hpp"
#include "Rendering/Vulkan/VulkanDescriptor.hpp"
#include "Rendering/Vulkan/VulkanRenderer.hpp"
#include "ResourceManager/ResourceManager.hpp"


class Viewport : public IWindowPanel
{
public:
    explicit Viewport(Editor* a_editor, const std::string& a_windowIdentifier) : IWindowPanel(a_editor, a_windowIdentifier) {}
    

    ImVec2 m_lastSize{ 0.0f, 0.0f };

    //VkSampler sampler{};
    ImTextureID dSets {};

    inline void Init() override
    {
        InitIcons();
        dSets = reinterpret_cast<ImTextureID>(ImGui_ImplVulkan_AddTexture(ResourceManager::GetInstance().GetStandardSampler(), p_editor->GetEngine()->GetRenderer()->CastVulkan()->GetViewportImageView(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL));
    };

    void Update() override {};
    void Render() override;
    void Destroy() override {};

    void InitIcons();
    std::shared_ptr<ITexture> LoadTexture(const Engine* engine, const std::string& path);

private:
    std::shared_ptr<ITexture> m_iconMove, m_iconRotate, m_iconResize, m_iconPlay, m_iconStop;
    ImTextureID m_iconMoveID = NULL;
    ImTextureID m_iconRotateID = NULL;
    ImTextureID m_iconResizeID = NULL;
    ImTextureID m_iconPlayID = NULL;
    ImTextureID m_iconStopID = NULL;
};
