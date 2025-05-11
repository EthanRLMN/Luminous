#include "Game/Scene.hpp"

#include "Game/Systems/Entity/Entity.hpp"
#include "Game/Systems/Entity/EntityFactory.hpp"
#include "Game/Systems/Entity/EntityTemplates.hpp"

void Scene::SceneEntity(EntityManager& a_entityManager)
{
    EntityTemplates templates;
    templates.RegisterEntityTemplates();

    std::shared_ptr<Entity> l_cube = a_entityManager.CreateEntityFromTemplate("Cube");
    std::shared_ptr<Entity> l_cube2 = a_entityManager.CreateEntityFromTemplate("Sphere");

    /*const std::shared_ptr<VikingRoom> l_vikingRoom = std::make_shared<VikingRoom>(a_entityManager);
    l_vikingRoom->Register();*/

    /*const std::shared_ptr<Player> l_player = std::make_shared<Player>(a_entityManager);
    l_player->Register();

    const std::shared_ptr<Cube> l_cube = std::make_shared<Cube>(a_entityManager);
    l_cube->Register();*/

    /*std::shared_ptr<Entity> l_testEntity = EntityFactory::Get().CreateEntity("Test Entity", a_entityManager);
    if (l_testEntity) l_testEntity->Register();*/
}
