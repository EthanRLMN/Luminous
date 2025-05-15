#include "Game/Scene.hpp"

#include "Game/Systems/Time.inl"
#include "Game/Systems/Entity/EntityFactory.hpp"
#include "Game/Systems/Entity/EntityTemplates.hpp"



void Scene::RegisterScene(EntityManager& a_entityManager)
{
    const std::string filepath = "Engine/Assets/Default/Save/Scene.json";
    const rfl::Result<EntityData> result = rfl::json::load<EntityData>(filepath);

    EntityTemplates l_defaultTemplates{};
    l_defaultTemplates.RegisterEntityTemplates();

    LoadScene(filepath, a_entityManager);

    for (size_t i = 0; i < EntityManager::GetAvailableTemplates().size(); ++i)
    {
        const std::shared_ptr<Entity> l_obj = a_entityManager.CreateEntityFromTemplate(EntityManager::GetAvailableTemplates()[i]);

        const Maths::Vector3 l_position = Maths::Vector3(4.0f, 0.0f, 0.0f) * i;
        l_obj->Transform()->SetLocalPosition(l_position);
    }

    for (const auto& l_entity : EntityManager::GetAvailableTemplates())
        DEBUG_LOG_CRITICAL("{}", l_entity);

}

void Scene::LoadScene(std::string filename, const EntityManager& a_entityManager)
{
    if (!CheckIfFileDetected(filename))
    {
        DEBUG_LOG_CRITICAL("Scene doesn't exist: {}", filename);
        return;
    }

    const rfl::Result<std::vector<EntityData>> l_result = rfl::json::load<std::vector<EntityData>>(filename);
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
                        l_light->GetLight().m_count = compData.count;
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
            l_lightData.count = l_light->GetLight().m_count;

            l_datasaver.componentType = "Light";
            l_datasaver.components.emplace_back(l_lightData);
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
        DEBUG_LOG_ERROR("File Not Detected");
        return false;
    }
    DEBUG_LOG_ERROR("File Detected");
    return true;
}
