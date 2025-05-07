#pragma once

#include "EntitySystem/Entity.hpp"
#include "EntitySystem/EntityComponent.hpp"
#include "EntitySystem/EntityManager.hpp"
#include "EntitySystem/Components/ModelComponent.hpp"
#include "EntitySystem/Components/RigidbodyComponent.hpp"
#include <Logger.hpp>



class Player : public EntityComponent, public std::enable_shared_from_this<Player>
{
public:
    explicit Player(EntityManager& a_entityManager) : m_entityManager(a_entityManager)
    {

        m_playerEntity = a_entityManager.CreateEntity();
        m_playerEntity->SetName("Player");

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

    }

    void GameplayStarted() override
    {

        DEBUG_LOG_INFO("[Player] Gameplay Started");
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
    std::shared_ptr<RigidbodyComponent> m_rigidbodyComponent = std::make_shared<RigidbodyComponent>();
    std::shared_ptr<ModelComponent> m_modelComponent = std::make_shared<ModelComponent>();

    EntityManager& m_entityManager;
};
