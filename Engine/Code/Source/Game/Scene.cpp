#include "Game/Scene.hpp"
#include "Logger.hpp"

#include "EntitySystem/Components/CTransform.hpp"

void Scene::SceneEntity()
{
    //CReate Manager
    EntityManager entityManager;


    //Player TEST
    size_t playerEntityId = entityManager.CreateEntity();
    Entity& playerEntity = entityManager.GetEntity(playerEntityId);

    playerEntity.AddComponent<CTransform>();



    //Floor Test
    size_t FloorEntityId = entityManager.CreateEntity();
    Entity& FloorEntity = entityManager.GetEntity(FloorEntityId);

    FloorEntity.AddComponent<CTransform>();



    //Debug player position
    std::shared_ptr<CTransform> transformComp = playerEntity.GetComponent<CTransform>();
    if (transformComp)
    {
        std::cout << "PlayerEntityID : " << playerEntityId << "    Position :";
        std::cout << transformComp->position.x << ", ";
        std::cout << transformComp->position.y << ", ";
        std::cout << transformComp->position.z  << std::endl;
    }

  
     // Debug Floor position
    std::shared_ptr<CTransform> transformComp2 = FloorEntity.GetComponent<CTransform>();
    if (transformComp2)
    {
        std::cout << "FloorID : " << FloorEntityId << "    Position :";
        std::cout << transformComp2->position.x << ", ";
        std::cout << transformComp2->position.y << ", ";
        std::cout << transformComp2->position.z << std::endl;
    }

    


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
