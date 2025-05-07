#include "Game/Scene.hpp"
#include "Logger.hpp"

#include "EntitySystem/Entity.hpp"

#include "Game/Scripts/Player.hpp"
#include "Game/Scripts/Weapon.hpp"
#include "Game/Scripts/PlayerModel.hpp"

/*
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
}*/

void Scene::SceneEntity(EntityManager& a_entityManager)
{
    /*
    const std::shared_ptr<Player> l_player = std::make_shared<Player>(a_entityManager);
    l_player->Register();

    const std::shared_ptr<Weapon> l_weapon = std::make_shared<Weapon>(a_entityManager, l_player->GetEntity());
    l_weapon->Register();*/

    ;

    const std::shared_ptr<PlayerModel> l_player = std::make_shared<PlayerModel>(a_entityManager);
    l_player->Register();
    

    const std::shared_ptr<PlayerModel> l_model2 = std::make_shared<PlayerModel>(a_entityManager);
    l_model2->Register();
}
