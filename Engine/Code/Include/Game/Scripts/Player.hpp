#pragma once
#include "Entity.hpp"
#include "EntityComponent.hpp"
#include "Components/CModel.hpp"
#include "Components/CRigidbody.hpp"
#include "Components/CTransform.hpp"

class Player : public EntityComponent, public std::enable_shared_from_this<Player>
{
public:
    Player(EntityManager& entityManager) :
        entityManager(entityManager)
    {

        playerEntity = entityManager.CreateEntity();
        playerEntity->SetName("Player");

        playerEntity->AddComponent(transformComponent);
        playerEntity->AddComponent(rigidbodyComponent);
        playerEntity->AddComponent(modelComponent);
    }

    void Register()
    {
        entityManager.RegisterLogic(shared_from_this());
    }

    void Initialize() override
    {
        std::cout << "[Player] Initialize" << std::endl;
        Input();
        rigidbodyComponent->simulatePhysic = true;
        modelComponent->SetModelPath("Assets/Player.fbx");
        std::cout << "Player Has CHild : " << playerEntity->HasChildren() << std::endl;
        std::cout << "Player  Has Parent : " << playerEntity->HasParent() << std::endl;
    }

    void GameplayStarted() override
    {
        std::cout << "[Player] Gameplay Started" << std::endl;
        std::cout << "Player Model : " << modelComponent->GetModelPath() << std::endl;
    }

    void Update() override
    {
        std::cout << "[Player] Update Tick" << std::endl;
    }

    void Input()
    {
        std::cout << "Input A = sauter" << std::endl;
    }

    std::shared_ptr<Entity> GetEntity() const
    {
        return playerEntity;
    }


private:
    std::shared_ptr<Entity> playerEntity;
    EntityManager& entityManager;

    std::shared_ptr<TransformComponent> transformComponent = std::make_shared<TransformComponent>();
    std::shared_ptr<RigidbodyComponent> rigidbodyComponent = std::make_shared<RigidbodyComponent>();
    std::shared_ptr<ModelComponent> modelComponent = std::make_shared<ModelComponent>();
};
