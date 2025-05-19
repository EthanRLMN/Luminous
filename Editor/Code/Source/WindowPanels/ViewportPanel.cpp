#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

#include "WindowPanels/ViewportPanel.hpp"

#include "Rendering/Vulkan/VulkanRenderer.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"
#include "Rendering/Vulkan/VulkanTexture.hpp"
#include "ResourceManager/ResourceManager.hpp"

static const std::filesystem::path s_IconPath = "Editor/Assets/Icons/";


void Viewport::Init()
{
    InitIcons();
    dSets = reinterpret_cast<ImTextureID>(ImGui_ImplVulkan_AddTexture(ResourceManager::GetInstance().GetStandardSampler(), p_editor->GetEngine()->GetRenderer()->CastVulkan()->GetViewportImageView(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL));
}


void Viewport::Render()
{
    m_camera = p_editor->GetEngine()->GetRenderer()->CastVulkan()->GetCamera();
    IWindowPanel::Render();

    ImGui::Begin(p_windowIdentifier.c_str(), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground);
    ImGuizmo::BeginFrame();

    RenderToolbarButtons();
    UpdateTextureIfNeeded();
    const ViewportImageInfo l_imageInfo = RenderViewportImage();
    RenderGizmo(l_imageInfo);

    ImGui::End();
}


void Viewport::InitIcons()
{
    m_iconMove = LoadTexture(p_editor->GetEngine(), (s_IconPath / "MoveIcon.png").string());
    m_iconRotate = LoadTexture(p_editor->GetEngine(), (s_IconPath / "RotateIcon.png").string());
    m_iconResize = LoadTexture(p_editor->GetEngine(), (s_IconPath / "ResizeIcon.png").string());
    m_iconPlay = LoadTexture(p_editor->GetEngine(), (s_IconPath / "PlayIcon.png").string());
    m_iconStop = LoadTexture(p_editor->GetEngine(), (s_IconPath / "StopIcon.png").string());

    auto loadImg = [&](const std::shared_ptr<ITexture>& tex, ImTextureID& id)
    {
        tex->CastVulkan()->CreateTextureImageView(p_editor->GetEngine()->GetDevice());
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


void Viewport::RenderToolbarButtons()
{
    const ImVec2 l_avail = ImGui::GetContentRegionAvail();
    constexpr float l_buttonWidth = 40.0f;
    constexpr float l_buttonHeight = 40.0f;
    constexpr ImVec2 l_buttonSize(l_buttonWidth, l_buttonHeight);

    if (ImGui::ImageButton("Move", m_iconMoveID, l_buttonSize))
        m_currentGizmoOperation = ImGuizmo::TRANSLATE;

    ImGui::SameLine();
    if (ImGui::ImageButton("Rotate", m_iconRotateID, l_buttonSize))
        m_currentGizmoOperation = ImGuizmo::ROTATE;

    ImGui::SameLine();
    if (ImGui::ImageButton("Resize", m_iconResizeID, l_buttonSize))
        m_currentGizmoOperation = ImGuizmo::SCALE;

    ImGui::SameLine(0, 0.4f * l_avail.x);

    if (ImGui::ImageButton("Play", m_iconPlayID, l_buttonSize))
        { /* TODO: Action */ }

    ImGui::SameLine();
    if (ImGui::ImageButton("Stop", m_iconStopID, l_buttonSize))
        { /* TODO: Action */ }
}


void Viewport::UpdateTextureIfNeeded()
{
    VulkanRenderer* l_renderer = p_editor->GetEngine()->GetRenderer()->CastVulkan();
    if (l_renderer->m_recreateDsets)
    {
        l_renderer->m_recreateDsets = false;

        dSets = reinterpret_cast<ImTextureID>(ImGui_ImplVulkan_AddTexture(
            ResourceManager::GetInstance().GetStandardSampler(),
            l_renderer->GetViewportImageView(),
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL));
    }
}


void Viewport::RenderGizmo(const ViewportImageInfo& a_imageInfo) const
{
    const std::shared_ptr<Entity> l_selectedEntity = p_editor->GetSelectedEntity();
    if (!l_selectedEntity)
        return;

    const std::shared_ptr<TransformComponent> l_transform = l_selectedEntity->GetComponent<TransformComponent>();
    if (!l_transform)
        return;

    const Maths::Matrix4 l_model = l_transform->GetGlobalMatrix().Transpose();
    const Maths::Matrix4 l_view = m_camera.GetViewMatrix().Transpose();
    const Maths::Matrix4 l_projection = m_camera.GetProjectionMatrix();

    float l_modelMatrix[16];
    float l_viewMatrix[16];
    float l_projMatrix[16];

    memcpy(l_modelMatrix, &l_model.mat, sizeof(float) * 16);
    memcpy(l_viewMatrix, &l_view.mat, sizeof(float) * 16);
    memcpy(l_projMatrix, &l_projection.mat, sizeof(float) * 16);

    ImGuizmo::SetOrthographic(false);
    ImGuizmo::Enable(true);
    ImGuizmo::SetDrawlist();

    ImGuizmo::SetRect(a_imageInfo.m_position.x, a_imageInfo.m_position.y, a_imageInfo.m_size.x, a_imageInfo.m_size.y);

    ImGuizmo::Manipulate(
        l_viewMatrix,
        l_projMatrix,
        m_currentGizmoOperation,
        ImGuizmo::WORLD,
        l_modelMatrix);

    if (ImGuizmo::IsUsing())
    {
        Maths::Matrix4 l_newModelMatrix;
        memcpy(&l_newModelMatrix.mat, l_modelMatrix, sizeof(float) * 16);
        l_newModelMatrix = l_newModelMatrix.Transpose();

        if (l_transform->HasParent())
        {
            Maths::Matrix4 l_parentMatrix = l_transform->GetParent()->Transform()->GetGlobalMatrix().Inverse();
            l_newModelMatrix = l_parentMatrix * l_newModelMatrix;
        }

        Maths::Vector3 l_translation, l_scale;
        Maths::Quaternion l_rotation;
        l_newModelMatrix.Decompose(l_translation, l_rotation, l_scale);

        switch (m_currentGizmoOperation)
        {
            case ImGuizmo::TRANSLATE:
                l_transform->SetLocalPosition(l_translation);
                break;

            case ImGuizmo::ROTATE:
                l_transform->SetLocalRotationQuat(l_rotation);
                break;

            case ImGuizmo::SCALE:
                l_transform->SetLocalScale(l_scale);
                break;

            default:
                break;
        }
    }
}


Viewport::ViewportImageInfo Viewport::RenderViewportImage() const
{
    const VkExtent2D l_extent = p_editor->GetEngine()->GetSwapChain()->CastVulkan()->GetSwapChainExtent();

    const float l_texWidth = static_cast<float>(l_extent.width);
    const float l_texHeight = static_cast<float>(l_extent.height);
    const float l_aspectRatio = l_texWidth / l_texHeight;

    const ImVec2 l_avail = ImGui::GetContentRegionAvail();
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

    const ImVec2 l_finalPos(l_screenPos.x + l_offsetX, l_screenPos.y + l_offsetY);
    ImGui::SetCursorScreenPos(l_finalPos);
    ImGui::Image(dSets, l_imageSize);

    return { l_finalPos, l_imageSize };
}