#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

#include "WindowPanels/ViewportPanel.hpp"

#include "Rendering/Vulkan/VulkanSwapChain.hpp"
#include "Rendering/Vulkan/VulkanTexture.hpp"
#include "ResourceManager/ResourceManager.hpp"

static const std::filesystem::path s_IconPath = "Editor/Assets/Icons/";

void Viewport::Render()
{
    m_camera = p_editor->GetEngine()->GetRenderer()->CastVulkan()->GetCamera();
    IWindowPanel::Render();

    ImGui::Begin(p_windowIdentifier.c_str(), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground);
    ImGuizmo::BeginFrame();

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

    Maths::Matrix4 view = m_camera.GetViewMatrix().Transpose();
    Maths::Matrix4 projection = m_camera.GetProjectionMatrix();

    const auto selectedEntity = p_editor->GetSelectedEntity();

    if (selectedEntity)
    {
        std::shared_ptr<TransformComponent> transform = selectedEntity->GetComponent<TransformComponent>();
        if (transform)
        {
            Maths::Matrix4 model = transform->GetGlobalMatrix().Transpose();
            float modelMatrix[16];
            memcpy(modelMatrix, &model.mat, sizeof(float) * 16);

            ImGuizmo::SetOrthographic(false);
            ImGuizmo::Enable(true);
            ImGuizmo::SetDrawlist();

            ImVec2 winPos = ImGui::GetWindowViewport()->Pos;

            ImGuizmo::SetRect(winPos.x + l_offsetX, winPos.y + l_offsetY, l_imageSize.x, l_imageSize.y);


            float viewMatrix[16];
            memcpy(viewMatrix, &view.mat, sizeof(float) * 16);

            float projMatrix[16];
            memcpy(projMatrix, &projection.mat, sizeof(float) * 16);
            
            ImGuizmo::Manipulate(
                    viewMatrix,
                    projMatrix,
                    m_currentGizmoOperation,
                    ImGuizmo::LOCAL,
                    modelMatrix);


            if (ImGuizmo::IsUsing())
            {
                // Convert back to Matrix4
                Maths::Matrix4 newModelMatrix;
                memcpy(&newModelMatrix.mat, modelMatrix, sizeof(float) * 16);

                // Transpose back to column-major if needed
                newModelMatrix = newModelMatrix.Transpose();

                // Décomposer la matrice en position / rotation / scale
                Maths::Vector3 translation, scale;
                Maths::Quaternion rotation;
                newModelMatrix.Decompose(translation, rotation, scale);

                transform->SetGlobalPosition(translation);
                transform->SetGlobalRotationQuat(rotation); // ou quaternion si besoin
                transform->SetGlobalScale(scale);
            }
        }
    }

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
