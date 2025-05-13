#include "Game/Scene.hpp"

#include "Game/Systems/Time.inl"
#include "Game/Systems/Entity/EntityFactory.hpp"
#include "Game/Systems/Entity/EntityTemplates.hpp"

void Scene::RegisterScene(EntityManager& a_entityManager)
{
    EntityTemplates l_defaultTemplates {};
    l_defaultTemplates.RegisterEntityTemplates();

    for (int i = 0; i < EntityManager::GetAvailableTemplates().size(); ++i)
    {
        auto l_obj = a_entityManager.CreateEntityFromTemplate(EntityManager::GetAvailableTemplates()[i]);

        Maths::Vector3 l_position = Maths::Vector3(4.0f, 0.0f, 0.0f) * i;
        l_obj->Transform()->SetLocalPosition(l_position);
    }

    for (const auto& l_entity : EntityManager::GetAvailableTemplates())
    {
    }

    for (const auto& l_entity : EntityManager::GetAvailableTemplates())
    {
        DEBUG_LOG_CRITICAL("{}", l_entity);
    }

    for (const auto& l_entity : a_entityManager.GetEntities())
    {
        DEBUG_LOG_CRITICAL("ENTITY = {}", l_entity->GetUUID());
    }
}
