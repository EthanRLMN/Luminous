#pragma once
#include "EntitySystem/Entity.hpp"
#include "EntitySystem/EntityComponent.hpp"
#include "EntitySystem/Components/CModel.hpp"
#include "EntitySystem/Components/CRigidbody.hpp"
#include "EntitySystem/Components/CTransform.hpp"

class Player : public EntityComponent, public std::enable_shared_from_this<Player>
{
public:
    Player(EntityManager& entityManager) :
        m_entityManager(entityManager)
    {

        m_playerEntity = entityManager.CreateEntity();
        m_playerEntity->SetName("Player");

        m_playerEntity->AddComponent(transformComponent);
        m_playerEntity->AddComponent(rigidbodyComponent);
        m_playerEntity->AddComponent(modelComponent);
    }

    void Register()
    {
        m_entityManager.RegisterLogic(shared_from_this());
    }

    void Initialize() override
    {
        DEBUG_LOG_INFO("[Player] Initialize");
        Input();
        rigidbodyComponent->m_simulatePhysic = true;
        modelComponent->SetModelPath("Assets/Player.fbx");

        DEBUG_LOG_INFO("Player Has CHild :  {}", modelComponent->GetModelPath());
        DEBUG_LOG_INFO("Player  Has Parent : {}", modelComponent->GetModelPath());
    }

    void GameplayStarted() override
    {

        DEBUG_LOG_INFO("[Player] Gameplay Started");
        DEBUG_LOG_INFO("Player Model : {}", modelComponent->GetModelPath());
    }

    void Update() override
    {
        DEBUG_LOG_INFO("[Player] Update Tick ");
    }

    void Input()
    {
        DEBUG_LOG_INFO("Input A  = sauter");
    }

    std::shared_ptr<Entity> GetEntity() const
    {
        return m_playerEntity;
    }


private:
    std::shared_ptr<Entity> m_playerEntity;
    EntityManager& m_entityManager;

    std::shared_ptr<TransformComponent> transformComponent = std::make_shared<TransformComponent>();
    std::shared_ptr<RigidbodyComponent> rigidbodyComponent = std::make_shared<RigidbodyComponent>();
    std::shared_ptr<ModelComponent> modelComponent = std::make_shared<ModelComponent>();
};
