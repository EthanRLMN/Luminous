#include "Game/Scene.hpp"
#include "Logger.hpp"

#include "EntitySystem/Entity.hpp"

#include "Game/Scripts/Player.hpp"
#include "Game/Scripts/Weapon.hpp"


void Scene::SceneEntity()
{
    EntityManager entityManager;

    std::shared_ptr<Player> player = std::make_shared<Player>(entityManager);
    player->Register();

    std::shared_ptr<Weapon> weapon = std::make_shared<Weapon>(entityManager, player->GetEntity());
    weapon->Register();

    entityManager.Initialize();
    entityManager.GameplayStarted();
    entityManager.Update();
}
