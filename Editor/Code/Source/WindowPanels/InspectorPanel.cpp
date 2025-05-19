#include "backends/imgui_impl_vulkan.h"
#include "imgui.h"


#include "WindowPanels/InspectorPanel.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "WindowPanels/FileExplorerPanel.hpp"

enum class TransformMode
{
    Local,
    Global
};

TransformMode m_transformMode = TransformMode::Local;

void InspectorPanel::MatrixToArray(const Maths::Matrix4& matrix, float out[16])
{
    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col)
            out[col + row * 4] = matrix.mat[row][col];
}

void InspectorPanel::SetSelectedEntity(const std::shared_ptr<Entity>& entity)
{
    p_isEntitySelected = entity;
}

Maths::Matrix4 InspectorPanel::ArrayToMatrix(const float in[16])
{
    Maths::Matrix4 result;
    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col)
            result.mat[row][col] = in[col + row * 4];
    return result;
}

void InspectorPanel::Render()
{
    IWindowPanel::Render();

    if (p_isOpen)
    {
        ImGui::Begin(p_windowIdentifier.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);

        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::MenuItem("Add Component")) {}
            ImGui::EndPopup();
        }

        if (p_isEntitySelected)
        {
            //ImGui::InputText("", );
            if (ImGui::CollapsingHeader("Transform"))
            {
                if (ImGui::BeginCombo("Transform Mode", m_transformMode == TransformMode::Local ? "Local" : "Global"))
                {
                    if (ImGui::Selectable("Local", m_transformMode == TransformMode::Local))
                        m_transformMode = TransformMode::Local;
                    if (ImGui::Selectable("Global", m_transformMode == TransformMode::Global))
                        m_transformMode = TransformMode::Global;
                    ImGui::EndCombo();
                }

                Maths::Vector3 position = (m_transformMode == TransformMode::Local)
                                                  ? p_isEntitySelected->Transform()->GetLocalPosition()
                                                  : p_isEntitySelected->Transform()->GetGlobalPosition();

                Maths::Vector3 rotation = (m_transformMode == TransformMode::Local)
                                                  ? p_isEntitySelected->Transform()->GetLocalRotationVec()
                                                  : p_isEntitySelected->Transform()->GetGlobalRotationVec();

                Maths::Vector3 scale = (m_transformMode == TransformMode::Local)
                                               ? p_isEntitySelected->Transform()->GetLocalScale()
                                               : p_isEntitySelected->Transform()->GetGlobalScale();

                const float inputWidth = 150.0f;

                ImGui::Text("Position");
                bool posChanged = false;
                ImGui::PushItemWidth(inputWidth);
                ImGui::Text("X:");
                ImGui::SameLine();
                posChanged |= ImGui::InputFloat("##posX", &position.x, 0.1f, 1.0f, "%.2f");
                ImGui::SameLine();
                ImGui::Text("Y:");
                ImGui::SameLine();
                posChanged |= ImGui::InputFloat("##posY", &position.y, 0.1f, 1.0f, "%.2f");
                ImGui::SameLine();
                ImGui::Text("Z:");
                ImGui::SameLine();
                posChanged |= ImGui::InputFloat("##posZ", &position.z, 0.1f, 1.0f, "%.2f");
                ImGui::PopItemWidth();

                ImGui::Text("Rotation");
                bool rotChanged = false;
                ImGui::PushItemWidth(inputWidth);
                ImGui::Text("X:");
                ImGui::SameLine();
                rotChanged |= ImGui::InputFloat("##rotX", &rotation.x, 0.1f, 1.0f, "%.2f");
                ImGui::SameLine();
                ImGui::Text("Y:");
                ImGui::SameLine();
                rotChanged |= ImGui::InputFloat("##rotY", &rotation.y, 0.1f, 1.0f, "%.2f");
                ImGui::SameLine();
                ImGui::Text("Z:");
                ImGui::SameLine();
                rotChanged |= ImGui::InputFloat("##rotZ", &rotation.z, 0.1f, 1.0f, "%.2f");
                ImGui::PopItemWidth();

                ImGui::Text("Scale");
                bool scaleChanged = false;
                ImGui::PushItemWidth(inputWidth);
                ImGui::Text("X:");
                ImGui::SameLine();
                scaleChanged |= ImGui::InputFloat("##scaleX", &scale.x, 0.1f, 1.0f, "%.2f");
                ImGui::SameLine();
                ImGui::Text("Y:");
                ImGui::SameLine();
                scaleChanged |= ImGui::InputFloat("##scaleY", &scale.y, 0.1f, 1.0f, "%.2f");
                ImGui::SameLine();
                ImGui::Text("Z:");
                ImGui::SameLine();
                scaleChanged |= ImGui::InputFloat("##scaleZ", &scale.z, 0.1f, 1.0f, "%.2f");
                ImGui::PopItemWidth();

                if (m_transformMode == TransformMode::Local)
                {
                    if (posChanged)
                        p_isEntitySelected->Transform()->SetLocalPosition(position);
                    if (rotChanged)
                        p_isEntitySelected->Transform()->SetLocalRotationVec(rotation);
                    if (scaleChanged)
                        p_isEntitySelected->Transform()->SetLocalScale(scale);
                }

                if (m_transformMode == TransformMode::Global)
                {
                    if (posChanged)
                        p_isEntitySelected->Transform()->SetGlobalPosition(position);
                    if (rotChanged)
                        p_isEntitySelected->Transform()->SetGlobalRotationVec(rotation);
                    if (scaleChanged)
                        p_isEntitySelected->Transform()->SetGlobalScale(scale);
                }
            }

            if (ImGui::CollapsingHeader("Mesh Renderer"))
            {
                if (auto modelComponent = p_isEntitySelected->GetComponent<ModelComponent>())
                {
                    const std::string& meshPath = modelComponent->GetMeshPath();
                    const std::string& texturePath = modelComponent->GetTexturePath();

                    std::string currentMeshName = meshPath.empty() ? "None" : meshPath.substr(meshPath.find_last_of("/\\") + 1);
                    ImGui::Text("Mesh:");

                    if (ImGui::Button((currentMeshName + "##mesh").c_str(), ImVec2(200, 0))) {}

                    if (ImGui::BeginDragDropTarget())
                    {
                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FILE_DRAG"))
                        {
                            const char* droppedPath = static_cast<const char*>(payload->Data);
                            std::string pathStr = std::string(droppedPath);

                            if (pathStr.ends_with(".obj") || pathStr.ends_with(".fbx") || pathStr.ends_with(".gltf"))
                            {
                                modelComponent->SetMesh(pathStr);
                                modelComponent->SetMeshPath(pathStr);
                            }
                        }
                        ImGui::EndDragDropTarget();
                    }

                    std::string currentTextureName = texturePath.empty() ? "None" : texturePath.substr(texturePath.find_last_of("/\\") + 1);
                    ImGui::Text("Texture:");

                    static std::unordered_map<std::string, ImTextureID> s_textureCache;

                    ImTextureID textureID = NULL;
                    if (!texturePath.empty())
                    {
                        if (!s_textureCache.contains(texturePath))
                        {
                            std::shared_ptr<ITexture> texture = LoadTexture(p_editor->GetEngine(), texturePath);
                            texture->CastVulkan()->CreateTextureImageView(p_editor->GetEngine()->GetDevice());

                            textureID = reinterpret_cast<ImTextureID>(
                                    ImGui_ImplVulkan_AddTexture(
                                            ResourceManager::GetInstance().GetRendererSampler(),
                                            texture->CastVulkan()->GetTextureImageView(),
                                            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL));

                            s_textureCache[texturePath] = textureID;
                        }

                        textureID = s_textureCache[texturePath];
                    }

                    if (textureID)
                    {
                        ImGui::Image(textureID, ImVec2(128, 128));
                    }

                    if (ImGui::BeginDragDropTarget())
                    {
                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FILE_DRAG"))
                        {
                            const char* droppedPath = static_cast<const char*>(payload->Data);
                            std::string pathStr = std::string(droppedPath);

                            if (pathStr.ends_with(".png") || pathStr.ends_with(".jpg") || pathStr.ends_with(".jpeg"))
                            {
                                std::string oldTexture = texturePath;
                                modelComponent->SetTexture(pathStr);
                                modelComponent->SetTexturePath(pathStr);
                                s_textureCache.erase(oldTexture);
                            }
                        }
                        ImGui::EndDragDropTarget();
                    }
                }
            }


            /*
            p_isEntitySelected->Transform()->SetLocalPosition(newPosition);
            p_isEntitySelected->Transform()->SetLocalRotationQuat(Maths::Quaternion::FromEulerAngles(newEuler));
            p_isEntitySelected->Transform()->SetLocalScale(newScale);*/
        }
        ImGui::PopStyleColor();
        ImGui::End();
    }
}

std::array<float, 16> InspectorPanel::ToFloatArray(const Maths::Matrix4& matrix)
{
    std::array<float, 16> flatArray;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            flatArray[i * 4 + j] = matrix.mat[i][j];
        }
    }
    return flatArray;
}
