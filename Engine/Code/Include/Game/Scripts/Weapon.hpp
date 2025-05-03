#pragma once

#include "EntitySystem/Entity.hpp"
#include "EntitySystem/EntityComponent.hpp"
#include "EntitySystem/Components/ModelComponent.hpp"
#include "EntitySystem/Components/TransformComponent.hpp"


#include "Player.hpp"

class Weapon : public EntityComponent, public std::enable_shared_from_this<Weapon>
{
public:
    Weapon(EntityManager& a_entityManager, const std::shared_ptr<Entity>& a_playerEntity) : m_playerEntity(a_playerEntity), m_entityManager(a_entityManager)
    {

        m_weaponEntity = a_entityManager.CreateEntity();
        m_weaponEntity->SetName("Weapon");

        m_weaponEntity->AddComponent(m_transformComponent);
        m_weaponEntity->AddComponent(m_modelComponent);

        m_modelComponent->SetModelPath("Assets/Sword.obj");
        a_playerEntity->AttachChild(m_weaponEntity);
        m_weaponEntity->SetParent(m_weaponEntity);
    }

    void Register()
    {
        m_entityManager.RegisterLogic(shared_from_this());
    }

    void Initialize() override
    {
        DEBUG_LOG_INFO("[Weapon] Initialize");

        DEBUG_LOG_INFO("Weapon Has CHild : {}", m_weaponEntity->HasChildren());
        DEBUG_LOG_INFO("Weapon  Has Parent : ", m_weaponEntity->HasParent());

    }

    void GameplayStarted() override
    {

        DEBUG_LOG_INFO("[Weapon] Gameplay Started");
        DEBUG_LOG_INFO("Weapon Model : :{}", m_modelComponent->GetModelPath());
    }

    void Update() override
    {
        DEBUG_LOG_INFO("[Weapon] Update Tick");
    }

    std::shared_ptr<Entity> GetEntity() const
    {
        return m_weaponEntity;
    }

private:
    std::shared_ptr<Entity> m_weaponEntity { nullptr };
    std::shared_ptr<Entity> m_playerEntity { nullptr };
    std::shared_ptr<TransformComponent> m_transformComponent = std::make_shared<TransformComponent>();
    std::shared_ptr<ModelComponent> m_modelComponent = std::make_shared<ModelComponent>();

    EntityManager& m_entityManager;
};
