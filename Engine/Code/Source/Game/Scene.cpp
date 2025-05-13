#include "Game/Scene.hpp"

#include "Game/Systems/Time.inl"
#include "Game/Systems/Entity/EntityFactory.hpp"
#include "Game/Systems/Entity/EntityTemplates.hpp"



void Scene::RegisterScene(EntityManager& a_entityManager)
{
    const rfl::Result<Entity_Saver> result = rfl::json::load<Entity_Saver>("Engine/Assets/Default/Save/Scene.json");

    const std::string filepath = "Engine/Assets/Default/Save/Scene.json";

    if (!std::filesystem::exists(filepath)) 
    {
        DEBUG_LOG_CRITICAL("JSon Not find = {}", filepath);
    } 
    else
    {
        DEBUG_LOG_INFO("Load File Json");
    }


    EntityTemplates l_defaultTemplates {};
    l_defaultTemplates.RegisterEntityTemplates();

    a_entityManager.CreateEntityFromTemplate("Companion");


    Entity_Saver entitySaver; 




    for (const auto& l_entity : EntityManager::GetAvailableTemplates())
    {
        DEBUG_LOG_CRITICAL("{}", l_entity);
    }

    for (const auto& l_entity : a_entityManager.GetEntities())
    {
        //DEBUG_LOG_CRITICAL("ENTITY = {}", l_entity->GetUUID());
        l_entity->SetActive(entitySaver.isActive);
        DEBUG_LOG_CRITICAL("ENTITY is active ? = {}",l_entity->IsActive());
    }
}
