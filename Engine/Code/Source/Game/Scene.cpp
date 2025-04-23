#include "Game/Scene.hpp"
#include "Logger.hpp"

#include "EntitySystem/Components/CTransform.hpp"

void Scene::SceneEntity()
{
    EntityManager entityManager;

    size_t playerEntityId = entityManager.CreateEntity();
    Entity& playerEntity = entityManager.GetEntity(playerEntityId);

    playerEntity.AddComponent<CTransform>();

    std::shared_ptr<CTransform> transformComp = playerEntity.GetComponent<CTransform>();
    if (transformComp)
    {
       // DEBUG_LOG_INFO("PlayerPosition :", transformComp->position);
        // DEBUG_LOG_INFO("PlayerRotation :", transformComp->rotation);
        // DEBUG_LOG_INFO("PlayerScale :", transformComp->scale);
    }

    entityManager.DestroyEntity(playerEntityId);

    try
    {
        entityManager.GetEntity(playerEntityId);
    } catch (const std::out_of_range& e)
    {
        DEBUG_LOG_ERROR("Entity not found: ", e.what());
    }
}
