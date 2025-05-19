#include "backends/imgui_impl_vulkan.h"
#include "imgui.h"

#include "Game/Systems/Component/CameraComponent.hpp"
#include "Game/Systems/Component/LightComponent.hpp"
#include "Game/Systems/Component/MeshRendererComponent.hpp"
#include "Game/Systems/Component/RigidbodyComponent.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "WindowPanels/FileExplorerPanel.hpp"
#include "WindowPanels/InspectorPanel.hpp"

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

        if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup) && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
        {
            if (!ImGui::IsAnyItemHovered())
            {
                ImGui::OpenPopup("AddComponentPopup");
            }
        }

        if (ImGui::BeginPopup("AddComponentPopup"))
        {
            if (ImGui::BeginMenu("Add new Component..."))
            {
                if (ImGui::MenuItem("Mesh renderer"))
                {
                    auto meshRendererComponent = std::make_shared<ModelComponent>();
                    p_isEntitySelected->AddComponent(std::static_pointer_cast<EntityComponent>(meshRendererComponent));
                }
                if (ImGui::MenuItem("Light"))
                {
                    auto lightComponent = std::make_shared<LightComponent>();
                    p_isEntitySelected->AddComponent(lightComponent);
                }
                if (ImGui::MenuItem("Box RigidBody"))
                {
                    auto rigidbodyComponent = std::make_shared<RigidbodyComponent>();

                    rigidbodyComponent->SetEngine(p_isEntitySelected->GetEngine());
                    rigidbodyComponent->SetEntity(p_isEntitySelected);
                    rigidbodyComponent->SetColliderType(BOXCOLLIDER);
                    rigidbodyComponent->Initialize();
                    p_isEntitySelected->AddComponent(std::static_pointer_cast<EntityComponent>(rigidbodyComponent));
                }
                if (ImGui::MenuItem("Sphere RigidBody"))
                {
                    auto rigidbodyComponent = std::make_shared<RigidbodyComponent>();

                    rigidbodyComponent->SetEngine(p_isEntitySelected->GetEngine());
                    rigidbodyComponent->SetEntity(p_isEntitySelected);
                    rigidbodyComponent->SetColliderType(SPHERECOLLIDER);
                    rigidbodyComponent->Initialize();
                    p_isEntitySelected->AddComponent(std::static_pointer_cast<EntityComponent>(rigidbodyComponent));
                }
                if (ImGui::MenuItem("Capsule RigidBody"))
                {
                    auto rigidbodyComponent = std::make_shared<RigidbodyComponent>();

                    rigidbodyComponent->SetEngine(p_isEntitySelected->GetEngine());
                    rigidbodyComponent->SetEntity(p_isEntitySelected);
                    rigidbodyComponent->SetColliderType(CAPSULECOLLIDER);
                    rigidbodyComponent->Initialize();
                    p_isEntitySelected->AddComponent(std::static_pointer_cast<EntityComponent>(rigidbodyComponent));
                }
                if (ImGui::MenuItem("Camera"))
                {
                    auto cameraComponent = std::make_shared<CameraComponent>();
                    p_isEntitySelected->AddComponent(cameraComponent);
                }
                ImGui::EndMenu();
            }
            ImGui::EndPopup();
        }


        if (p_isEntitySelected)
        {
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

                ImGui::Text("Rotation");
                bool rotChanged = false;
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

                ImGui::Text("Scale");
                bool scaleChanged = false;
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
                } else
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
                    if (ImGui::BeginPopupContextItem("DeleteComponents"))
                    {
                        if (ImGui::MenuItem("Delete Component"))
                        {
                            auto component = p_isEntitySelected->GetComponent<ModelComponent>();
                            if (component)
                            {
                                p_isEntitySelected->RemoveComponent(component);
                            }
                        }
                        ImGui::EndPopup();
                    }
                }
            }

            if (auto lightComponent = p_isEntitySelected->GetComponent<LightComponent>())
            {
                if (ImGui::CollapsingHeader("Light Component"))
                {

                    float l_color[3];
                    l_color[0] = lightComponent->GetColor().x;
                    l_color[1] = lightComponent->GetColor().y;
                    l_color[2] = lightComponent->GetColor().z;
                    bool bColorChanged = false;
                    ImGui::Text("Color");

                    bColorChanged |= ImGui::ColorPicker3("##color", l_color);

                    float l_intensity = lightComponent->GetIntensity();
                    bool bIntensityChanged = false;
                    ImGui::Text("Intensity");
                    bIntensityChanged |= ImGui::InputFloat("##intensity", &l_intensity, 0.1f, 1.0f, "%.2f");

                    float l_ambient = lightComponent->GetAmbientStrength();
                    bool bAmbientChanged = false;
                    ImGui::Text("AmbientStrength");
                    bAmbientChanged |= ImGui::InputFloat("##ambient", &l_ambient, 0.1f, 1.0f, "%.2f");

                    float l_specular = lightComponent->GetSpecularStrength();
                    bool bSpecularChanged = false;
                    ImGui::Text("SpecularStrength");
                    bSpecularChanged |= ImGui::InputFloat("##specular", &l_specular, 0.1f, 1.0f, "%.2f");

                    LightType l_lightType = lightComponent->GetType();
                    int l_typeInt = static_cast<int>(l_lightType);
                    bool bTypeChanged = false;
                    ImGui::Text("Light Type");
                    bTypeChanged |= ImGui::InputInt("##type", &l_typeInt);


                    if (l_lightType == LightType::DIRECTIONAL)
                    {
                        const float inputWidth = 150.0f;

                        Maths::Vector3 l_direction = p_isEntitySelected->GetComponent<LightComponent>()->GetDirection();
 
                        // --- Position
                        ImGui::Text("Direction");
                        bool posChanged = false;
                        ImGui::PushItemWidth(inputWidth);
                        ImGui::Text("X:");
                        ImGui::SameLine();
                        posChanged |= ImGui::InputFloat("##posX", &l_direction.x, 0.1f, 1.0f, "%.2f");
                        ImGui::SameLine();
                        ImGui::Text("Y:");
                        ImGui::SameLine();
                        posChanged |= ImGui::InputFloat("##posY", &l_direction.y, 0.1f, 1.0f, "%.2f");
                        ImGui::SameLine();
                        ImGui::Text("Z:");
                        ImGui::SameLine();
                        posChanged |= ImGui::InputFloat("##posZ", &l_direction.z, 0.1f, 1.0f, "%.2f");

                        if(posChanged)
                            p_isEntitySelected->GetComponent<LightComponent>()->SetDirection(l_direction);
                    }


                    if (l_typeInt < 0)
                        l_typeInt = 0;
                    else if (l_typeInt > 1)
                        l_typeInt = 1;

                    if (bIntensityChanged)
                        lightComponent->SetIntensity(l_intensity);

                    if (bAmbientChanged)
                        lightComponent->SetAmbientStrength(l_ambient);

                    if (bSpecularChanged)
                        lightComponent->SetSpecularStrength(l_specular);

                    if (bTypeChanged)
                        lightComponent->SetType(static_cast<LightType>(l_typeInt));

                    if (bColorChanged)
                        lightComponent->SetColor(Maths::Vector3(l_color[0], l_color[1], l_color[2]));
                }
                if (ImGui::BeginPopupContextItem("DeleteComponents"))
                {
                    if (ImGui::MenuItem("Delete Component"))
                    {
                        auto component = p_isEntitySelected->GetComponent<LightComponent>();
                        if (component)
                        {
                            p_isEntitySelected->RemoveComponent(component);
                        }
                    }
                    ImGui::EndPopup();
                }
            }

            if (auto rigidbodyComponent = p_isEntitySelected->GetComponent<RigidbodyComponent>())
            {
                ColliderType l_type = rigidbodyComponent->GetColliderType();
                std::string typeString = "";
                if (l_type == BOXCOLLIDER)
                    typeString = "Box ";
                else if (l_type == SPHERECOLLIDER)
                    typeString = "Sphere ";
                else if (l_type == CAPSULECOLLIDER)
                    typeString = "Capsule ";

                if (ImGui::CollapsingHeader((typeString + "Rigidbody Component").c_str()))
                {

                    if (l_type == BOXCOLLIDER)
                    {
                        Maths::Vector3 l_boxSizeOffset = p_isEntitySelected->GetComponent<RigidbodyComponent>()->GetBoxOffset();
                        const float inputWidth = 150.0f;

                        float l_min = -0.8f;

                        ImGui::Text("Box Size Offset");
                        bool posChanged = false;
                        ImGui::PushItemWidth(inputWidth);
                        ImGui::Text("X:");
                        ImGui::SameLine();
                        posChanged |= ImGui::InputFloat("##posX", &l_boxSizeOffset.x, 0.1f, 1.0f, "%.2f");
                        ImGui::SameLine();
                        ImGui::Text("Y:");
                        ImGui::SameLine();
                        posChanged |= ImGui::InputFloat("##posY", &l_boxSizeOffset.y, 0.1f, 1.0f, "%.2f");
                        ImGui::SameLine();
                        ImGui::Text("Z:");
                        ImGui::SameLine();
                        posChanged |= ImGui::InputFloat("##posZ", &l_boxSizeOffset.z, 0.1f, 1.0f, "%.2f");
                        ImGui::PopItemWidth();


                        std::string l_layerString = "";
                        JPH::ObjectLayer l_layer = p_isEntitySelected->GetComponent<RigidbodyComponent>()->GetLayer();
                        int l_layerInt;
                        bool layerChanged = false;
                        if (l_layer == Layers::DYNAMIC)
                        {
                            l_layerInt = 0;
                            l_layerString = "Layer : Dynamic";
                        } else if (l_layer == Layers::KINEMATIC)
                        {
                            l_layerInt = 1;
                            l_layerString = "Layer : Kinematic";
                        }
                        ImGui::Text(l_layerString.c_str());

                        layerChanged |= ImGui::InputInt("##layer", &l_layerInt);

                        if (l_layerInt < 0)
                            l_layerInt = 0;
                        else if (l_layerInt > 1)
                            l_layerInt = 1;

                        JPH::uint8 l_finalLayer;
                        if (l_layerInt == 0)
                            l_finalLayer = Layers::DYNAMIC;
                        else
                            l_finalLayer = Layers::KINEMATIC;


                        if (layerChanged)
                            p_isEntitySelected->GetComponent<RigidbodyComponent>()->SetLayer(l_finalLayer);

                        if (posChanged)
                            p_isEntitySelected->GetComponent<RigidbodyComponent>()->SetColliderSize(l_boxSizeOffset);
                    } else if (l_type == SPHERECOLLIDER)
                    {

                        float l_sphereOffset = p_isEntitySelected->GetComponent<RigidbodyComponent>()->GetSphereOffset();
                        bool bSizeOffsetChange = false;
                        ImGui::Text("Sphere size offset");
                        bSizeOffsetChange |= ImGui::InputFloat("##spheresize", &l_sphereOffset, 0.1f, 1.0f, "%.2f");


                        std::string l_layerString = "";
                        JPH::ObjectLayer l_layer = p_isEntitySelected->GetComponent<RigidbodyComponent>()->GetLayer();
                        int l_layerInt;
                        bool layerChanged = false;
                        if (l_layer == Layers::DYNAMIC)
                        {
                            l_layerInt = 0;
                            l_layerString = "Layer : Dynamic";
                        } else if (l_layer == Layers::KINEMATIC)
                        {
                            l_layerInt = 1;
                            l_layerString = "Layer : Kinematic";
                        }
                        ImGui::Text(l_layerString.c_str());

                        layerChanged |= ImGui::InputInt("##layer", &l_layerInt);

                        if (l_layerInt < 0)
                            l_layerInt = 0;
                        else if (l_layerInt > 1)
                            l_layerInt = 1;

                        JPH::uint8 l_finalLayer;
                        if (l_layerInt == 0)
                            l_finalLayer = Layers::DYNAMIC;
                        else
                            l_finalLayer = Layers::KINEMATIC;


                        if (bSizeOffsetChange)
                            p_isEntitySelected->GetComponent<RigidbodyComponent>()->SetColliderSize(l_sphereOffset);

                        if (layerChanged)
                            p_isEntitySelected->GetComponent<RigidbodyComponent>()->SetLayer(l_finalLayer);

                    } else if (l_type == CAPSULECOLLIDER)
                    {

                        Maths::Vector2 l_capsuleSizeOffset = p_isEntitySelected->GetComponent<RigidbodyComponent>()->GetCapsuleOffset();
                        const float inputWidth = 150.0f;

                        float l_min = -0.8f;

                        ImGui::Text("Capsule Size Offset");
                        bool posChanged = false;
                        ImGui::PushItemWidth(inputWidth);
                        ImGui::Text("Radius:");
                        ImGui::SameLine();
                        posChanged |= ImGui::InputFloat("##posX", &l_capsuleSizeOffset.x, 0.1f, 1.0f, "%.2f");
                        ImGui::SameLine();
                        ImGui::Text("Height:");
                        ImGui::SameLine();
                        posChanged |= ImGui::InputFloat("##posY", &l_capsuleSizeOffset.y, 0.1f, 1.0f, "%.2f");


                        std::string l_layerString = "";
                        JPH::ObjectLayer l_layer = p_isEntitySelected->GetComponent<RigidbodyComponent>()->GetLayer();
                        int l_layerInt;
                        bool layerChanged = false;
                        if (l_layer == Layers::DYNAMIC)
                        {
                            l_layerInt = 0;
                            l_layerString = "Layer : Dynamic";
                        } else if (l_layer == Layers::KINEMATIC)
                        {
                            l_layerInt = 1;
                            l_layerString = "Layer : Kinematic";
                        }
                        ImGui::Text(l_layerString.c_str());

                        layerChanged |= ImGui::InputInt("##layer", &l_layerInt);

                        if (l_layerInt < 0)
                            l_layerInt = 0;
                        else if (l_layerInt > 1)
                            l_layerInt = 1;

                        JPH::uint8 l_finalLayer;
                        if (l_layerInt == 0)
                            l_finalLayer = Layers::DYNAMIC;
                        else
                            l_finalLayer = Layers::KINEMATIC;

                        if (layerChanged)
                            p_isEntitySelected->GetComponent<RigidbodyComponent>()->SetLayer(l_finalLayer);


                        if (posChanged)
                            p_isEntitySelected->GetComponent<RigidbodyComponent>()->SetColliderSize(l_capsuleSizeOffset);
                    }
                }
                /* if (ImGui::BeginPopupContextItem("DeleteComponents"))
                {
                    if (ImGui::MenuItem("Delete Component"))
                    {
                        auto component = p_isEntitySelected->GetComponent<RigidbodyComponent>();
                        if (component)
                        {
                            p_isEntitySelected->RemoveComponent(component);
                        }
                    }
                    ImGui::EndPopup();
                }*/
            }


            if (auto modelComponent = p_isEntitySelected->GetComponent<CameraComponent>())
            {
                if (ImGui::CollapsingHeader("Camera Component"))
                {
                    float l_near = p_isEntitySelected->GetComponent<CameraComponent>()->GetNearPlane();
                    bool bNearChanged = false;
                    ImGui::Text("Near Plane");
                    bNearChanged |= ImGui::InputFloat("##near", &l_near, 0.1f, 1.0f, "%.2f");

                    float l_far = p_isEntitySelected->GetComponent<CameraComponent>()->GetFarPlane();
                    bool bFarChanged = false;
                    ImGui::Text("Far Plane");
                    bFarChanged |= ImGui::InputFloat("##far", &l_far, 0.1f, 1.0f, "%.2f");

                    float l_fov = p_isEntitySelected->GetComponent<CameraComponent>()->GetFieldOfView();
                    bool bFovChanged = false;
                    ImGui::Text("Field of View");
                    bFovChanged |= ImGui::InputFloat("##fov", &l_fov, 0.1f, 1.0f, "%.2f");

                    float l_aspectRatio = p_isEntitySelected->GetComponent<CameraComponent>()->GetAspectRatio();
                    bool bAspectRatioChanged = false;
                    ImGui::Text("Aspect Ratio");
                    bAspectRatioChanged |= ImGui::InputFloat("##aspectratio", &l_aspectRatio, 0.1f, 1.0f, "%.2f");
                    
                    bool l_mainCamera = p_isEntitySelected->GetComponent<CameraComponent>()->GetIsMainCamera();
                    bool bMainCameraChanged = false;
                    ImGui::Text("Main Camera");
                    bMainCameraChanged |= ImGui::Checkbox("##maincam", &l_mainCamera);


                    if (bNearChanged)
                        p_isEntitySelected->GetComponent<CameraComponent>()->SetNearPlane(l_near);

                    if (bFarChanged)
                        p_isEntitySelected->GetComponent<CameraComponent>()->SetFarPlane(l_far);

                    if (bFovChanged)
                        p_isEntitySelected->GetComponent<CameraComponent>()->SetFieldOfView(l_fov);

                    if (bAspectRatioChanged)
                        p_isEntitySelected->GetComponent<CameraComponent>()->SetAspectRatio(l_aspectRatio);

                    if (bMainCameraChanged)
                        p_isEntitySelected->GetComponent<CameraComponent>()->ForceSetMainCamera(l_mainCamera);

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
