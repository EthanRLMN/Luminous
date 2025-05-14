#include "Game/Scene.hpp"

#include "Game/Systems/Time.inl"
#include "Game/Systems/Entity/EntityFactory.hpp"
#include "Game/Systems/Entity/EntityTemplates.hpp"

Entity_Saver entitySaver;

void Scene::RegisterScene(EntityManager& a_entityManager)
{
    const std::string filepath = "Engine/Assets/Default/Save/Scene.json";
    const rfl::Result<Entity_Saver> result = rfl::json::load<Entity_Saver>(filepath);

    EntityTemplates l_defaultTemplates{};
    l_defaultTemplates.RegisterEntityTemplates();

    auto l_entity = a_entityManager.CreateEntityFromTemplate("Companion");

    LoadScene(filepath,a_entityManager);

    DEBUG_LOG_CRITICAL("name {} ", l_entity->GetName());

    for (const auto& l_entity : EntityManager::GetAvailableTemplates())
    {
        DEBUG_LOG_CRITICAL("{}", l_entity);
    }
    
}

void Scene::LoadScene(std::string filename,EntityManager& a_entityManager)
{ 
    
   if (!CheckIfFileDetected(filename))
    {
        DEBUG_LOG_CRITICAL("Scene don't exist: {}", filename);
        return;
    }

    const rfl::Result<std::vector<Entity_Saver>> result = rfl::json::load<std::vector<Entity_Saver>>(filename);
    if (!result)
    {
        DEBUG_LOG_CRITICAL("Error loading the JSON.");
        return;
    }

    const std::vector<Entity_Saver>& entityData = result.value();
    
    if (entityData.empty())
    {
        DEBUG_LOG_CRITICAL("The JSON file is empty or contains no entities.");
        return;
    }

    auto entityIt = a_entityManager.GetEntities().begin();
    for (const auto& data : entityData)
    {
        if (entityIt == a_entityManager.GetEntities().end())
        {
            DEBUG_LOG_CRITICAL("No more entities available in the manager.");
            break;
        }

        auto entity = *entityIt;
        entity->SetName(data.entityName);
        entity->SetUUID(data.entityUUID);
        entity->SetActive(data.isActive);

        ++entityIt; 
    }

    DEBUG_LOG_CRITICAL("Scene loaded successfully: {}", filename);
}

void Scene::SaveScene(const std::string& filepath, EntityManager& a_entityManager)
{
    std::vector<Entity_Saver> entityData;
    rfl::json::save(filepath, entityData);

    for (const auto& entity : a_entityManager.GetEntities())
    {
        Entity_Saver saver;
        saver.entityName = entity->GetName(); 
        saver.entityUUID = entity->GetUUID(); 
        saver.isActive = entity->IsActive(); 

        auto transform = entity->GetComponent<TransformComponent>();

        if (transform)
        {
            saver.globalPositionX =  transform->GetGlobalPosition().x;
            saver.globalPositionY = transform->GetGlobalPosition().y;
            saver.globalPositionZ = transform->GetGlobalPosition().z;

            saver.globalRotationX = transform->GetGlobalRotationQuat().x;
            saver.globalRotationY = transform->GetGlobalRotationQuat().y;
            saver.globalRotationZ = transform->GetGlobalRotationQuat().z;
            saver.globalRotationW = transform->GetGlobalRotationQuat().w;

            saver.globalScaleX = transform->GetGlobalScale().x;
            saver.globalScaleY = transform->GetGlobalScale().y;
            saver.globalScaleZ = transform->GetGlobalScale().z;

            //saver.localPosition = transform->GetLocalPosition();
            //saver.localRotation = transform->GetLocalRotationQuat();
            //saver.localScale = transform->GetLocalScale();
        }


        entityData.push_back(saver);
    }

    const std::string json_string = rfl::json::write(entityData, rfl::json::pretty);
    rfl::json::save(filepath, entityData, rfl::json::pretty);
}

bool Scene::CheckIfFileDetected(std::string filename)
{
    const std::string filepath = filename;

    if (!std::filesystem::exists(filepath))
    {
        return false;
        DEBUG_LOG_ERROR("File Not Detected 1 ");
    }
    else
    {
        return true;
        DEBUG_LOG_ERROR("File Detected 1 ");
    }
    return false;
    DEBUG_LOG_ERROR("File Not Detected 2 ");
}