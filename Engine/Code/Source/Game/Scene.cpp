#include "Game/Scene.hpp"

#include "Game/Systems/Time.inl"
#include "Game/Systems/Entity/EntityFactory.hpp"
#include "Game/Systems/Entity/EntityTemplates.hpp"

void Scene::RegisterScene(EntityManager& a_entityManager)
{
    EntityTemplates l_defaultTemplates {};
    l_defaultTemplates.RegisterEntityTemplates();

    a_entityManager.CreateEntityFromTemplate("Companion");


    for (const auto& l_entity : EntityManager::GetAvailableTemplates())
    {
        DEBUG_LOG_CRITICAL("{}", l_entity);
    }

    for (const auto& l_entity : a_entityManager.GetEntities())
    {
        DEBUG_LOG_CRITICAL("ENTITY = {}", l_entity->GetUUID());
    }
}
