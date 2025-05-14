#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

#include "WindowPanels/ViewportPanel.hpp"

#include "Rendering/Vulkan/VulkanRenderer.hpp"
#include "Rendering/Vulkan/VulkanTexture.hpp"

static const std::filesystem::path s_IconPath = "Editor/Assets/Icons/";

void Viewport::Render()
{
    IWindowPanel::Render();

    ImGui::Begin(p_windowIdentifier.c_str(), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground);
    
    ImVec2 avail = ImGui::GetContentRegionAvail();
    float buttonWidth = 40.f;
    float buttonHeight = 40.f;
    ImVec2 buttonSize(buttonWidth, buttonHeight);

    if (ImGui::ImageButton("Move", m_iconMoveID, buttonSize))
    {
        m_currentGizmoOperation = ImGuizmo::TRANSLATE;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton("Rotate", m_iconRotateID, buttonSize))
    {
        m_currentGizmoOperation = ImGuizmo::ROTATE;
    }
    ImGui::SameLine();
    if (ImGui::ImageButton("Resize", m_iconResizeID, buttonSize))
    {
        m_currentGizmoOperation = ImGuizmo::SCALE;
    }

    ImGui::SameLine(0, 0.4f * avail.x);

    if (ImGui::ImageButton("Play", m_iconPlayID, buttonSize)) 
    {
    
    }
    ImGui::SameLine();
    if (ImGui::ImageButton("Stop", m_iconStopID, buttonSize)) 
    {
    
    }

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


    ImGui::Image(reinterpret_cast<ImTextureID>(dSets), l_imageSize);

    ImGuizmo::SetDrawlist();
    ImGuizmo::SetOrthographic(false);
    ImGuizmo::SetRect(l_screenPos.x + l_offsetX, l_screenPos.y + l_offsetY, l_imageSize.x, l_imageSize.y);

    //CameraEditor* camera = m_camera.Update(static_cast<float>(a_swapChain->CastVulkan()->GetSwapChainExtent().width) / static_cast<float>(a_swapChain->CastVulkan()->GetSwapChainExtent().height));;
    Maths::Matrix4 view = m_camera->GetViewMatrix();
    Maths::Matrix4 projection = m_camera->GetProjectionMatrix();

    std::shared_ptr<TransformComponent> transform = p_isEntitySelected->GetComponent<TransformComponent>();
    Maths::Matrix4 model = transform->GetGlobalMatrix();

    ImGuizmo::Manipulate(view.Data(),
                         projection.Data(),
                         m_currentGizmoOperation,
                         ImGuizmo::WORLD,
                         model.Data());

    if (ImGuizmo::IsUsing())
    {
        Maths::Vector3 pos, scale;
        Maths::Quaternion rot;

        model.Decompose(pos, rot, scale);

        transform->SetGlobalPosition(pos);
        transform->SetGlobalRotationQuat(rot);
        transform->SetGlobalScale(scale);
    }
    ImGui::End();
}

void Viewport::InitIcons()
{
    Engine* engine = p_editor->GetEngine();
    auto* device = engine->GetDevice();
    auto* renderer = engine->GetRenderer()->CastVulkan();

    m_iconMove = LoadTexture(engine, (s_IconPath / "MoveIcon.png").string());
    m_iconRotate = LoadTexture(engine, (s_IconPath / "RotateIcon.png").string());
    m_iconResize = LoadTexture(engine, (s_IconPath / "ResizeIcon.png").string());
    m_iconPlay = LoadTexture(engine, (s_IconPath / "PlayIcon.png").string());
    m_iconStop = LoadTexture(engine, (s_IconPath / "StopIcon.png").string());

    auto sampler = renderer->GetDefaultTextureSampler();

    auto loadImg = [&](std::shared_ptr<ITexture>& tex, ImTextureID& id)
    {
        tex->CastVulkan()->CreateTextureImageView(device);
        tex->CastVulkan()->CreateTextureSampler(device);
        id = reinterpret_cast<ImTextureID>(ImGui_ImplVulkan_AddTexture(
                sampler,
                tex->CastVulkan()->GetTextureImageView(),
                VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL));
    };

    loadImg(m_iconMove, m_iconMoveID);
    loadImg(m_iconRotate, m_iconRotateID);
    loadImg(m_iconResize, m_iconResizeID);
    loadImg(m_iconPlay, m_iconPlayID);
    loadImg(m_iconStop, m_iconStopID);
}

std::shared_ptr<ITexture> Viewport::LoadTexture(Engine* engine, const std::string& path)
{
    IResourceParams params{};
    params.m_device = engine->GetDevice();
    params.m_commandPool = engine->GetCommandPool();
    params.m_texturePath = path;

    auto texture = std::make_shared<VulkanTexture>();
    texture->CreateTextureImage(params.m_device, params.m_commandPool, params.m_texturePath);
    return texture;
}
