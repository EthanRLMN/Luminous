#include "Game/Scene.hpp"
#include "Logger.hpp"

#include "EntitySystem/Components/CTransform.hpp"

void Scene::SceneEntity()
{
    //Player TEST
    size_t playerEntityId = entityManager.CreateEntity();
    Entity& playerEntity = entityManager.GetEntity(playerEntityId);

    playerEntity.AddComponent<CTransform>();



    //Floor Test
    size_t FloorEntityId = entityManager.CreateEntity();
    Entity& FloorEntity = entityManager.GetEntity(FloorEntityId);

    FloorEntity.AddComponent<CTransform>();



    //Debug player position

    //std::cout << "Player Position" << playerEntity.GetComponent<CTransform>()->position.x << std::endl;

    playerEntity.GetComponent<CTransform>()->position.x = 5;

 
    //std::cout << "New Player Position" << playerEntity.GetComponent<CTransform>()->position.x << std::endl;
    


    // dESTROY Entity
    // entityManager.DestroyEntity(playerEntityId);


    //Debug to see if Entity is still Available
    try
    {
        entityManager.GetEntity(playerEntityId);
    } catch (const std::out_of_range& e)
    {
        DEBUG_LOG_ERROR("Entity not found: ", e.what());
    }
}
