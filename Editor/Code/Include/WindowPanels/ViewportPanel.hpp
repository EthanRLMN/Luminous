#pragma once
#include "stb_image.h"

#include "Interface/IWindowPanel.hpp"
#include "Rendering/Vulkan/VulkanRenderer.hpp"
#include "Rendering/Vulkan/VulkanDescriptor.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"
#include "backends/imgui_impl_vulkan.h"
#include "InspectorPanel.hpp"
#include "Game/Systems/Camera/CameraEditor.hpp"
#include "Game/Systems/Component/TransformComponent.hpp"

class Viewport : public IWindowPanel
{
public:
    explicit Viewport(Editor* a_editor, const std::string& a_windowIdentifier) : IWindowPanel(a_editor, a_windowIdentifier) 
    {
        dSets = ImGui_ImplVulkan_AddTexture(p_editor->GetEngine()->GetRenderer()->CastVulkan()->GetViewportImageSampler(), p_editor->GetEngine()->GetRenderer()->CastVulkan()->GetViewportImageView(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
        InitIcons();
        float aspectRatio = static_cast<float>(
                                    p_editor->GetEngine()->GetSwapChain()->CastVulkan()->GetSwapChainExtent().width) /
                            static_cast<float>(
                                    p_editor->GetEngine()->GetSwapChain()->CastVulkan()->GetSwapChainExtent().height);
        m_camera = std::make_unique<CameraEditor>();
        m_camera->Init(aspectRatio, 60.0f, 0.1f, 100.0f);
    };
    

    ImVec2 m_lastSize{ 0.0f, 0.0f };

    VkSampler sampler{};
    VkDescriptorSet dSets;

    void Init() override {};
    void Update() override {};
    void Render() override;
    void Destroy() override {};

    void InitIcons();
    std::shared_ptr<ITexture> LoadTexture(Engine* engine, const std::string& path);

private:
    std::shared_ptr<ITexture> m_iconMove, m_iconRotate, m_iconResize, m_iconPlay, m_iconStop;
    ImTextureID m_iconMoveID = NULL;
    ImTextureID m_iconRotateID = NULL;
    ImTextureID m_iconResizeID = NULL;
    ImTextureID m_iconPlayID = NULL;
    ImTextureID m_iconStopID = NULL;

    ImGuizmo::OPERATION m_currentGizmoOperation = ImGuizmo::TRANSLATE;
    std::unique_ptr<CameraEditor> m_camera;
};
