#include "Game/Scene.hpp"
#include "Logger.hpp"

#include "EntitySystem/Entity.hpp"

#include "Game/Scripts/Player.hpp"
#include "Game/Scripts/VikingRoom.hpp"
#include "Engine.hpp"

void Scene::SceneEntity(EntityManager& a_entityManager)
{
    const std::shared_ptr<VikingRoom> l_viking_room = std::make_shared<VikingRoom>(a_entityManager);
    l_viking_room->Register();
     
    const std::shared_ptr<Player> l_player = std::make_shared<Player>(a_entityManager);
    l_player->Register();
}
