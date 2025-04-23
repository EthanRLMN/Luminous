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

        dSets = ImGui_ImplVulkan_AddTexture(p_editor->GetEngine()->GetRenderingDraw()->CastVulkan()->m_viewportSampler, p_editor->GetEngine()->GetRenderingDraw()->CastVulkan()->m_viewportImageview, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    };


    VkSampler sampler;
    VkDescriptorSet dSets;

    void Init() override {};
    void Update() override {};
    void Draw() override;
    void Destroy() override {};
};
