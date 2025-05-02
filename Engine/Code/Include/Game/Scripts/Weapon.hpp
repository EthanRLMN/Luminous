#pragma once
#include "Entity.hpp"
#include "EntityComponent.hpp"
#include "Components/CModel.hpp"
#include "Components/CRigidbody.hpp"
#include "Components/CTransform.hpp"


#include "Player.hpp"

class Weapon : public EntityComponent, public std::enable_shared_from_this<Weapon>
{
public:
    Weapon(EntityManager& entityManager, std::shared_ptr<Entity> playerEntity) :
        entityManager(entityManager), playerEntity(playerEntity)
    {

        weaponEntity = entityManager.CreateEntity();
        weaponEntity->SetName("Weapon");



        weaponEntity->AddComponent(transformComponent);
        weaponEntity->AddComponent(modelComponent);

        modelComponent->SetModelPath("Assets/Sword.obj");
        playerEntity->AttachChild(weaponEntity);
        weaponEntity->SetParent(weaponEntity);
    }

    void Register()
    {
        entityManager.RegisterLogic(shared_from_this());
    }

    void Initialize() override
    {
        std::cout << "[Weapon] Initialize" << std::endl;
        std::cout << "Weapon Has CHild : " << weaponEntity->HasChildren() << std::endl;
        std::cout << "Weapon  Has Parent : " << weaponEntity->HasParent() << std::endl;
    }

    void GameplayStarted() override
    {
        std::cout << "[Weapon] Gameplay Started" << std::endl;
        std::cout << "Weapon Model : " << modelComponent->GetModelPath() << std::endl;
    }

    void Update() override
    {
        std::cout << "[Weapon] Update Tick" << std::endl;
    }

    std::shared_ptr<Entity> GetEntity() const
    {
        return weaponEntity;
    }

private:
    std::shared_ptr<Entity> weaponEntity;
    std::shared_ptr<Entity> playerEntity;


    std::shared_ptr<TransformComponent> transformComponent = std::make_shared<TransformComponent>();
    std::shared_ptr<ModelComponent> modelComponent = std::make_shared<ModelComponent>();

    EntityManager& entityManager;
};
