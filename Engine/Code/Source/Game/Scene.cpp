#include "Game/Scene.hpp"

#include "Game/Systems/Time.inl"
#include "Game/Systems/Entity/EntityFactory.hpp"
#include "Game/Systems/Entity/EntityTemplates.hpp"

Entity_Saver entitySaver;


void Scene::RegisterScene(EntityManager& a_entityManager)
{
    const std::string filepath = "Engine/Assets/Default/Save/Scene.json";
    const rfl::Result<Entity_Saver> result = rfl::json::load<Entity_Saver>(filepath);

   // EnterScene(filepath);

    EntityTemplates l_defaultTemplates {};
    l_defaultTemplates.RegisterEntityTemplates();

    auto l_entity = a_entityManager.CreateEntityFromTemplate("Companion");

    LoadScene(filepath,a_entityManager);

    DEBUG_LOG_CRITICAL("name {} ", l_entity->GetName());

    for (const auto& l_entity : EntityManager::GetAvailableTemplates())
    {
        DEBUG_LOG_CRITICAL("{}", l_entity);
    }



    /*
    for (const auto& l_entity : a_entityManager.GetEntities())
    {
       
        DEBUG_LOG_CRITICAL("ENTITY = {}", l_entity->IsActive());
    }*/
   // SaveScene(filepath,a_entityManager);
    
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

        entityData.push_back(saver);
    }

    const std::string json_string = rfl::json::write(entityData, rfl::json::pretty);
    rfl::json::save(filepath, entityData, rfl::json::pretty);
}

void Scene::EnterScene(std::string filename)
{
    if (CheckIfFileDetected(filename))
    {
        if (IsEmpty(filename))
        {
            // load new Scene
        } 
        else
        {
           // LoadScene(filename);
        }
    }
}


bool Scene::CheckIfFileDetected(std::string filename)
{
    const std::string filepath = filename;

    if (!std::filesystem::exists(filepath))
    {
        return false;
    }
    else
    {
        return true;
    }
    return false;
}

bool Scene::IsEmpty(std::string filename)
{
    return false;
}   
