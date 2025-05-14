#include "WindowPanels/InspectorPanel.hpp"

#include "imgui.h"

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
            if (ImGui::MenuItem("Add Component"))
            {
            }
            ImGui::EndPopup();
        }

        if (p_isEntitySelected)
        {
            if (ImGui::CollapsingHeader("Transform"))
            {
                Maths::Vector3 position = p_isEntitySelected->Transform()->GetLocalPosition();
                Maths::Vector3 rotation = p_isEntitySelected->Transform()->GetLocalRotationVec();
                Maths::Vector3 scale = p_isEntitySelected->Transform()->GetLocalScale();

                const float inputWidth = 150.0f;

                // Position
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
                if (posChanged)
                    p_isEntitySelected->Transform()->SetLocalPosition(position);
                ImGui::PopItemWidth();

                // Rotation
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
                if (rotChanged)
                    p_isEntitySelected->Transform()->SetLocalRotationVec(rotation);
                ImGui::PopItemWidth();

                // Scale
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
                if (scaleChanged)
                    p_isEntitySelected->Transform()->SetLocalScale(scale);
                ImGui::PopItemWidth();
            }

            if (ImGui::CollapsingHeader("Mesh Renderer"))
            {
                if (auto modelComponent = p_isEntitySelected->GetComponent<ModelComponent>())
                {
                    std::string meshName = modelComponent->GetMeshPath();
                    std::string textureName = modelComponent->GetTexturePath();

                    std::string currentMeshName = meshName.substr(meshName.find_last_of("/\\") + 1);
                    ImGui::Text("Mesh:");

                    if(ImGui::Button((currentMeshName + "##mesh").c_str(), ImVec2(200, 0)))
                    {
                    }

                    if (ImGui::BeginDragDropTarget())
                    {
                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FILE_DRAG"))
                        {
                            const char* droppedPath = static_cast<const char*>(payload->Data);
                            std::string pathStr = std::string(droppedPath);

                            if (pathStr.ends_with(".obj") || pathStr.ends_with(".fbx") || pathStr.ends_with(".gltf"))
                            {
                                modelComponent->SetMesh(pathStr);
                                meshName = modelComponent->GetMeshPath();
                                currentMeshName = meshName.substr(meshName.find_last_of("/\\") + 1);
                            }
                        }
                        ImGui::EndDragDropTarget();
                    }


                    std::string currentTextureName = textureName.substr(textureName.find_last_of("/\\") + 1);
                    ImGui::Text("Texture:");

                    static std::unordered_map<std::string, ImTextureID> s_textureCache;

                    ImTextureID textureID = NULL;
                    if (!textureName.empty())
                    {
                        if (s_textureCache.find(textureName) == s_textureCache.end())
                        {
                            std::shared_ptr<ITexture> texture = LoadTexture(p_editor->GetEngine(), textureName);
                            texture->CastVulkan()->CreateTextureImageView(p_editor->GetEngine()->GetDevice());
                            texture->CastVulkan()->CreateTextureSampler(p_editor->GetEngine()->GetDevice());

                            auto descriptor = reinterpret_cast<ImTextureID>(
                                    ImGui_ImplVulkan_AddTexture(
                                            p_editor->GetEngine()->GetRenderer()->CastVulkan()->GetDefaultTextureSampler(),
                                            texture->CastVulkan()->GetTextureImageView(),
                                            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL));

                            s_textureCache[textureName] = descriptor;
                        }

                        textureID = s_textureCache[textureName];
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

                            if (pathStr.ends_with(".png") || pathStr.ends_with(".jpg"))
                            {
                                modelComponent->SetTexture(pathStr);
                                s_textureCache.erase(textureName);
                            }
                        }
                        ImGui::EndDragDropTarget();
                    }
                }
            }

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
