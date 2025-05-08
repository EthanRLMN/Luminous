#pragma once

#include "Interface/IWindowPanel.hpp"
#include "Rendering/Vulkan/VulkanRenderer.hpp"
#include "Rendering/Vulkan/VulkanDescriptor.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"
#include "backends/imgui_impl_vulkan.h"

class Viewport : public IWindowPanel
{
public:
    explicit Viewport(Editor* a_editor, const std::string& a_windowIdentifier) : IWindowPanel(a_editor, a_windowIdentifier) 
    {
        dSets = ImGui_ImplVulkan_AddTexture(p_editor->GetEngine()->GetRenderer()->CastVulkan()->GetViewportImageSampler(), p_editor->GetEngine()->GetRenderer()->CastVulkan()->GetViewportImageView(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    };
    

    ImVec2 m_lastSize{ 0.0f, 0.0f };

    VkSampler sampler{};
    VkDescriptorSet dSets;

    void Init() override {};
    void Update() override {};
    void Render() override;
    void Destroy() override {};
};
