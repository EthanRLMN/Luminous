#pragma once

#include "EntitySystem/Entity.hpp"
#include "EntitySystem/EntityComponent.hpp"
#include "EntitySystem/EntityManager.hpp"
#include "EntitySystem/Components/ModelComponent.hpp"
#include "EntitySystem/Components/RigidbodyComponent.hpp"
#include "EntitySystem/Components/TransformComponent.hpp"


class Player : public EntityComponent, public std::enable_shared_from_this<Player>
{
public:
    explicit Player(EntityManager& a_entityManager) : m_entityManager(a_entityManager)
    {

        m_playerEntity = a_entityManager.CreateEntity();
        m_playerEntity->SetName("Player");

        m_playerEntity->AddComponent(m_transformComponent);
        m_playerEntity->AddComponent(m_rigidbodyComponent);
        m_playerEntity->AddComponent(m_modelComponent);
    }

    void Register()
    {
        m_entityManager.RegisterLogic(shared_from_this());
    }

    void Initialize() override
    {
        DEBUG_LOG_INFO("[Player] Initialize");
        Input();
        m_rigidbodyComponent->m_simulatePhysic = true;
        m_modelComponent->SetModelPath("Assets/Player.fbx");

        DEBUG_LOG_INFO("Player Has CHild :  {}", m_modelComponent->GetModelPath());
        DEBUG_LOG_INFO("Player  Has Parent : {}", m_modelComponent->GetModelPath());
    }

    void GameplayStarted() override
    {

        DEBUG_LOG_INFO("[Player] Gameplay Started");
        DEBUG_LOG_INFO("Player Model : {}", m_modelComponent->GetModelPath());
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
    std::shared_ptr<Entity> m_playerEntity { nullptr };
    std::shared_ptr<TransformComponent> m_transformComponent = std::make_shared<TransformComponent>();
    std::shared_ptr<RigidbodyComponent> m_rigidbodyComponent = std::make_shared<RigidbodyComponent>();
    std::shared_ptr<ModelComponent> m_modelComponent = std::make_shared<ModelComponent>();

    EntityManager& m_entityManager;
};
