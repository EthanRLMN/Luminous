#pragma once

#include "EntitySystem/Components/ModelComponent.hpp"
#include "EntitySystem/Components/RigidbodyComponent.hpp"
#include "EntitySystem/Components/TransformComponent.hpp"
#include "EntitySystem/Entity.hpp"
#include "EntitySystem/EntityComponent.hpp"
#include "EntitySystem/EntityManager.hpp"


class PlayerModel : public EntityComponent, public std::enable_shared_from_this<PlayerModel>
{
public:
    explicit PlayerModel(EntityManager& a_entityManager) :
        m_entityManager(a_entityManager)
    {

        m_playerModelEntity = a_entityManager.CreateEntity();
        m_playerModelEntity->SetName("PlayerModel");

        m_playerModelEntity->AddComponent(m_transformComponent);
        m_playerModelEntity->AddComponent(m_modelComponent);
    }

    void Register()
    {
        m_entityManager.RegisterLogic(shared_from_this());
    }

    void Initialize() override
    {
        m_modelComponent->SetModelPath("Assets/Models/metalSonic.obj");
        m_transformComponent->TRS = Maths::Matrix4::TRS(Maths::Vector3(0.f, 0.f, 0.f), Maths::Vector3(0.f, 90.f, 90.f), Maths::Vector3(1.f, 1.0f, 1.0f));
    }

    void GameplayStarted() override
    {
    }

    void Update() override
    {
        
    }

    std::shared_ptr<Entity> GetEntity() const
    {
        return m_playerModelEntity;
    }


private:
    std::shared_ptr<Entity> m_playerModelEntity{ nullptr };
    std::shared_ptr<TransformComponent> m_transformComponent = std::make_shared<TransformComponent>();
    std::shared_ptr<RigidbodyComponent> m_rigidbodyComponent = std::make_shared<RigidbodyComponent>();
    std::shared_ptr<ModelComponent> m_modelComponent = std::make_shared<ModelComponent>();

    EntityManager& m_entityManager;
};
