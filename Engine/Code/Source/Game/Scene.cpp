#include "Game/Scene.hpp"

#include "Game/Scripts/Cube.hpp"
#include "Game/Scripts/Player.hpp"
#include "Game/Scripts/VikingRoom.hpp"
#include "Game/Systems/Entity/Entity.hpp"

void Scene::SceneEntity(EntityManager& a_entityManager)
{
    const std::shared_ptr<VikingRoom> l_vikingRoom = std::make_shared<VikingRoom>(a_entityManager);
    l_vikingRoom->Register();
     
    const std::shared_ptr<Player> l_player = std::make_shared<Player>(a_entityManager);
    l_player->Register();

    const std::shared_ptr<Cube> l_cube = std::make_shared<Cube>(a_entityManager);
    l_cube->Register();
}