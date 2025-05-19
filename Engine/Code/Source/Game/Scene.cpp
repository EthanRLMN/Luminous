#include "Game/Scene.hpp"

#include "Game/Systems/Time.inl"
#include "Game/Systems/Entity/EntityFactory.hpp"
#include "Game/Systems/Entity/EntityTemplates.hpp"

#include "Game/Systems/Component/RigidbodyComponent.hpp"
#include "Game/Systems/Component/ScriptComponent.hpp"

#include "Game/Systems/Scripts/ScriptManager.hpp"

#include "Game/Systems/Scripts/PlayerScript.hpp"

void Scene::RegisterScene(EntityManager& a_entityManager)
{
    const std::string filepath = "Engine/Assets/Default/Save/Scene.json";
    const rfl::Result<EntityData> result = rfl::json::load<EntityData>(filepath);

    EntityTemplates l_defaultTemplates{};
    l_defaultTemplates.RegisterEntityTemplates();

    LoadScene(filepath, a_entityManager);

    const std::shared_ptr<Entity> l_light = a_entityManager.CreateEntityFromTemplate("DefaultSphere");
    l_light->GetComponent<TransformComponent>()->SetLocalPosition(Maths::Vector3(0.f, 2.f, 3.f));
    const std::shared_ptr<LightComponent> l_lightComponent = std::make_shared<LightComponent>();
    l_light->AddComponent(l_lightComponent);
    l_lightComponent->SetColor(Maths::Vector3(1.0f, 0.0f, 0.0f));

    const std::shared_ptr<Entity> l_light2 = a_entityManager.CreateEntityFromTemplate("DefaultCube");
    l_light2->GetComponent<TransformComponent>()->SetLocalPosition(Maths::Vector3(4.f, 5.f, 3.f));
    const std::shared_ptr<LightComponent> l_lightComponent2 = std::make_shared<LightComponent>();
    l_light2->AddComponent(l_lightComponent2);
    l_lightComponent2->SetColor(Maths::Vector3(0.0f, 1.0f, 0.0f));


    for (size_t i = 0; i < EntityManager::GetAvailableTemplates().size(); ++i)
    {
        //const std::shared_ptr<Entity> l_obj = a_entityManager.CreateEntityFromTemplate(EntityManager::GetAvailableTemplates()[i]);

        //const Maths::Vector3 l_position = Maths::Vector3(4.0f, 0.0f, 0.0f) * static_cast<const float>(i);
        //l_obj->Transform()->SetLocalPosition(l_position);
    }


    /*
    const std::shared_ptr<Entity> collider = a_entityManager.CreateEntityFromTemplate("DefaultCube");
    const std::shared_ptr<Entity> collider2 = a_entityManager.CreateEntityFromTemplate("DefaultCube");
    collider->Transform()->SetLocalPosition(Maths::Vector3(9.5f, 10.0f, 0.0f));

    /*
    const std::shared_ptr<RigidbodyComponent> l_modelComponent = std::make_shared<RigidbodyComponent>();
    collider->AddComponent(l_modelComponent);
    l_modelComponent->SetEngine(a_entityManager.GetEngine());
    l_modelComponent->SetEntity(collider);
    collider->Transform()->SetLocalScale(Maths::Vector3(2.f, 2.5f, 2.f));
    collider->Transform()->SetLocalRotationVec(Maths::Vector3(0.f, 0.f, 40.f));

    l_modelComponent->SetLayer(Layers::DYNAMIC);
    l_modelComponent->SetActive(JPH::EActivation::Activate);
    l_modelComponent->SetColliderType(SPHERECOLLIDER);
    l_modelComponent->Initialize();

    collider->Transform()->SetLocalScale(Maths::Vector3(1.5f, 1.0f, 1.5f));
    l_modelComponent->SetColliderSize(Maths::Vector3(0.f, 0.f, 0.f));


    const std::shared_ptr<RigidbodyComponent> l_modelComponent2 = std::make_shared<RigidbodyComponent>();
    collider2->AddComponent(l_modelComponent2);
    l_modelComponent2->SetEngine(a_entityManager.GetEngine());
    l_modelComponent2->SetEntity(collider2);
    collider2->Transform()->SetLocalScale(Maths::Vector3(2.f, 2.5f, 2.f));
    collider2->Transform()->SetLocalRotationVec(Maths::Vector3(0.f, 0.f, 0.f));
    collider2->Transform()->SetLocalPosition(Maths::Vector3(8.f, 0.f, 0.0f));
    l_modelComponent2->SetLayer(Layers::KINEMATIC);
    l_modelComponent2->SetActive(JPH::EActivation::Activate);
    l_modelComponent2->SetColliderType(BOXCOLLIDER);
    l_modelComponent2->Initialize();

    collider2->Transform()->SetLocalScale(Maths::Vector3(1.f, 1.0f, 1.f));
    l_modelComponent2->SetColliderSize(Maths::Vector3(0.f, 0.f, 0.f));*/


    /*
    const std::shared_ptr<Entity> cam = a_entityManager.CreateEntityFromTemplate("DefaultEmpty");
    cam->GetComponent<TransformComponent>()->SetLocalPosition(Maths::Vector3(0.f, 0.f, -15.0f));
    cam->GetComponent<TransformComponent>()->SetLocalRotationVec(Maths::Vector3(0.f, 180.f, 0.f));
    const std::shared_ptr<CameraComponent> l_camComponent = std::make_shared<CameraComponent>();
    cam->AddComponent(l_camComponent);
    l_camComponent->Initialize();
    l_camComponent->ForceSetMainCamera(true);*/



    
    /*
    const std::shared_ptr<Entity> l_entityWithScript = a_entityManager.CreateEntityFromTemplate("DefaultCube");
    const std::shared_ptr<ScriptComponent> l_scriptComponent = std::make_shared<ScriptComponent>();
    BaseScript* l_script = new BaseScript();
    l_scriptComponent->SetScript(l_script);
    l_scriptComponent->Initialize();
    l_entityWithScript->AddComponent(l_scriptComponent);*/

    //--PLAYER INSTANTIATE--
    const std::shared_ptr<Entity> l_Player = a_entityManager.CreateEntityFromTemplate("DefaultEmpty");
    l_Player->SetName("Player");

    

    

    //-- Player Collider --
     const std::shared_ptr<RigidbodyComponent> l_playerCollider = std::make_shared<RigidbodyComponent>();
    l_playerCollider->SetColliderType(CAPSULECOLLIDER);
     l_Player->AddComponent(l_playerCollider);
    l_playerCollider->SetEngine(a_entityManager.GetEngine());
     l_playerCollider->SetEntity(l_Player);
    l_playerCollider->SetLayer(Layers::DYNAMIC);
    l_playerCollider->Initialize();
    l_playerCollider->GetRigidbody()->GetRigidBody()->GetMotionProperties()->SetInverseInertia(JPH::Vec3(0.f,1.f,0.f), JPH::Quat::sIdentity());
    l_playerCollider->GetRigidbody()->GetRigidBody()->SetAllowSleeping(false);
    JPH::MassProperties massProps = l_playerCollider->GetRigidbody()->GetShape()->GetMassProperties();
    l_Player->GetEngine()->GetPhysicsSystem()->GetBodyInterface().SetGravityFactor(l_playerCollider->GetRigidbody()->GetRigidBodyID(), 0.1f);
    
   // -- Player Script --
    const std::shared_ptr<ScriptComponent> l_scriptComponent = std::make_shared<ScriptComponent>();
    BaseScript* l_script = new PlayerScript();

    l_Player->AddComponent(l_scriptComponent);
    l_scriptComponent->SetScript(l_script);
    l_scriptComponent->Initialize();

    //For Camera
    const std::shared_ptr<Entity> l_Head = a_entityManager.CreateEntityFromTemplate("DefaultEmpty");
    l_Head->SetName("PlayerHead");
    l_Head->Transform()->SetParent(l_Player);

    //--PLAYER CAMERA--
    const std::shared_ptr<CameraComponent> l_camComponent = std::make_shared<CameraComponent>();
    l_Head->AddComponent(l_camComponent);

    l_camComponent->Initialize();
    l_camComponent->ForceSetMainCamera(true);



    //-- TEST PLATFORM--
    const std::shared_ptr<Entity> l_testPlatform = a_entityManager.CreateEntityFromTemplate("DefaultCube");
    l_testPlatform->SetName("Platform");
    l_testPlatform->GetComponent<TransformComponent>()->SetLocalPosition(Maths::Vector3(0.f, -6.f, 0.f));
    l_testPlatform->GetComponent<TransformComponent>()->SetLocalScale(Maths::Vector3(10.f, 0.5f, 10.f));
    const std::shared_ptr<RigidbodyComponent> l_platCollider = std::make_shared<RigidbodyComponent>();
    l_platCollider->SetColliderType(BOXCOLLIDER);
    l_platCollider->SetLayer(Layers::STATIC);
    l_testPlatform->AddComponent(l_platCollider);
    l_platCollider->SetEngine(a_entityManager.GetEngine());
    l_platCollider->SetEntity(l_testPlatform);
    l_platCollider->Initialize();
    

}

void Scene::LoadScene(std::string filename, const EntityManager& a_entityManager)
{
    if (!CheckIfFileDetected(filename))
    {
        DEBUG_LOG_CRITICAL("Scene doesn't exist: {}", filename);
        return;
    }

    const rfl::Result<std::vector<EntityData> > l_result = rfl::json::load<std::vector<EntityData> >(filename);
    if (!l_result)
    {
        DEBUG_LOG_CRITICAL("Error loading the JSON.");
        return;
    }

    const std::vector<EntityData>& l_entitiesData = l_result.value();

    if (l_entitiesData.empty())
    {
        DEBUG_LOG_CRITICAL("The JSON file is empty or contains no entities.");
        return;
    }

    auto l_entityIt = a_entityManager.GetEntities().begin();
    for (const auto& l_entityData : l_entitiesData)
    {
        if (l_entityIt == a_entityManager.GetEntities().end())
        {
            DEBUG_LOG_CRITICAL("No more entities available in the manager.");
            break;
        }

        std::shared_ptr<Entity> l_entity = *l_entityIt;
        l_entity->SetName(l_entityData.entityName);
        l_entity->SetUUID(l_entityData.entityUUID);
        l_entity->SetActive(l_entityData.isActive);

        for (const SerializedComponent& l_component : l_entityData.components)
        {
            rfl::visit([&]<typename T0>(T0&& compData)
            {
                using T = std::decay_t<T0>;

                if constexpr (std::is_same_v<T, TransformComponentData>)
                {
                    if (const std::shared_ptr<TransformComponent> l_transform = l_entity->GetComponent<TransformComponent>())
                    {
                        l_transform->SetGlobalPosition(Maths::Vector3(compData.globalPosition));
                        l_transform->SetGlobalRotationQuat(Maths::Quaternion(compData.globalRotation));
                        l_transform->SetGlobalScale(Maths::Vector3(compData.globalScale));
                        l_transform->SetLocalPosition(Maths::Vector3(compData.localPosition));
                        l_transform->SetLocalRotationQuat(Maths::Quaternion(compData.localRotation));
                        l_transform->SetLocalScale(Maths::Vector3(compData.localScale));
                    }
                }
                else if constexpr (std::is_same_v<T, ModelComponentData>)
                {
                    if (const std::shared_ptr<ModelComponent> l_model = l_entity->GetComponent<ModelComponent>())
                    {
                        l_model->SetMeshPath(compData.modelPath);
                        l_model->SetTexturePath(compData.texturePath);
                    }
                }
                else if constexpr (std::is_same_v<T, LightComponentData>)
                {
                    if (const std::shared_ptr<LightComponent> l_light = l_entity->GetComponent<LightComponent>())
                    {
                        l_light->GetLight().m_position = Maths::Vector3(compData.position);
                        l_light->GetLight().m_direction = Maths::Vector3(compData.direction);
                        l_light->GetLight().m_color = Maths::Vector3(compData.color);
                        l_light->GetLight().m_type = compData.type;
                        l_light->GetLight().m_intensity = compData.intensity;
                        l_light->GetLight().m_ambientStrength = compData.ambientStrength;
                        l_light->GetLight().m_specularStrength = compData.specularStrength;
                    }
                }
                else if constexpr (std::is_same_v<T, CameraComponentData>)
                {
                    if (const std::shared_ptr<CameraComponent> l_camera = l_entity->GetComponent<CameraComponent>())
                    {
                        l_camera->SetIsActive(compData.isActive);
                        l_camera->SetAspectRatio(compData.aspectRatio);
                        l_camera->SetFarPlane(compData.farPlane);
                        l_camera->SetNearPlane(compData.nearPlane);
                        l_camera->SetFieldOfView(compData.fieldOfView);
                    }
                }
            }, l_component);
        }
        ++l_entityIt;
    }
    DEBUG_LOG_CRITICAL("Scene loaded successfully: {}", filename);
}

void Scene::SaveScene(const std::string& filepath, const EntityManager& a_entityManager)
{
    std::vector<EntityData> l_entityData;

    for (const std::shared_ptr<Entity>& l_entity : a_entityManager.GetEntities())
    {
        EntityData l_datasaver;

        l_datasaver.entityName = l_entity->GetName();
        l_datasaver.entityUUID = l_entity->GetUUID();
        l_datasaver.isActive = l_entity->IsActive();

        if (const std::shared_ptr<TransformComponent>& l_transform = l_entity->GetComponent<TransformComponent>())
        {
            TransformComponentData l_transformData{};
            l_transformData.globalPosition = Vec3(l_transform->GetGlobalPosition());
            l_transformData.globalRotation = Quat(l_transform->GetGlobalRotationQuat());
            l_transformData.globalScale = Vec3(l_transform->GetGlobalScale());
            l_transformData.localPosition = Vec3(l_transform->GetLocalPosition());
            l_transformData.localRotation = Quat(l_transform->GetLocalRotationQuat());
            l_transformData.localScale = Vec3(l_transform->GetLocalScale());

            l_datasaver.componentType = "Transform";
            l_datasaver.components.emplace_back(l_transformData);
        }

        if (const std::shared_ptr<ModelComponent>& l_model = l_entity->GetComponent<ModelComponent>())
        {
            ModelComponentData l_modelData;
            l_modelData.modelPath = l_model->GetMeshPath();
            l_modelData.texturePath = l_model->GetTexturePath();

            l_datasaver.componentType = "Model";
            l_datasaver.components.emplace_back(l_modelData);
        }

        if (const std::shared_ptr<LightComponent>& l_light = l_entity->GetComponent<LightComponent>())
        {
            LightComponentData l_lightData{};
            l_lightData.position = Vec3(l_light->GetLight().m_position);
            l_lightData.direction = Vec3(l_light->GetLight().m_direction);
            l_lightData.color = Vec3(l_light->GetLight().m_color);
            l_lightData.type = l_light->GetLight().m_type;
            l_lightData.intensity = l_light->GetLight().m_intensity;
            l_lightData.ambientStrength = l_light->GetLight().m_ambientStrength;
            l_lightData.specularStrength = l_light->GetLight().m_specularStrength;

            l_datasaver.componentType = "Light";
            l_datasaver.components.emplace_back(l_lightData);
        }

        if (const std::shared_ptr<CameraComponent>& l_camera = l_entity->GetComponent<CameraComponent>())
        {
            CameraComponentData l_cameraData{};
            l_cameraData.aspectRatio = l_camera->GetAspectRatio();
            l_cameraData.farPlane = l_camera->GetFarPlane();
            l_cameraData.nearPlane = l_camera->GetNearPlane();
            l_cameraData.fieldOfView = l_camera->GetFieldOfView();
            l_cameraData.isActive = l_camera->IsActive();
            l_cameraData.eye = Vec3(l_camera->GetEye().x, l_camera->GetEye().y, l_camera->GetEye().z);
            l_cameraData.center = Vec3(l_camera->GetCenter().x, l_camera->GetCenter().y, l_camera->GetCenter().z);

            l_datasaver.componentType = "Camera";
            l_datasaver.components.emplace_back(l_cameraData);
        }

        l_entityData.push_back(l_datasaver);
    }
    rfl::json::save(filepath, l_entityData, rfl::json::pretty);
    DEBUG_LOG_INFO("Data was saved to file : {}!", filepath);
}

bool Scene::CheckIfFileDetected(const std::string& a_filename)
{
    const std::string& filepath = a_filename;

    if (!std::filesystem::exists(filepath))
    {
        DEBUG_LOG_ERROR("[SCENE] Could not find a proper scene file to load!");
        return false;
    }
    DEBUG_LOG_INFO("[SCENE] File `{}` found! Loading...", a_filename);
    return true;
}
