#pragma once

#include "EntitySystem/Entity.hpp"
#include "EntitySystem/EntityComponent.hpp"
#include "EntitySystem/EntityManager.hpp"
#include "EntitySystem/Components/ModelComponent.hpp"


class PlayerModel : public EntityComponent, public std::enable_shared_from_this<PlayerModel>
{
public:
    explicit PlayerModel(EntityManager& a_entityManager) : m_entityManager(a_entityManager)
    {

        m_playerModelEntity = a_entityManager.CreateEntity();
        m_playerModelEntity->SetName("PlayerModel");


        m_playerModelEntity->AddComponent(m_modelComponent);
    }

    void Register()
    {
        m_entityManager.RegisterLogic(shared_from_this());
    }

    void Initialize() override
    {
        m_playerModelEntity->SetTRS( Maths::Matrix4::TRS(Maths::Vector3::Zero, Maths::Vector3::Zero, Maths::Vector3::One));
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
    std::shared_ptr<Entity> m_playerModelEntity { nullptr };
    std::shared_ptr<ModelComponent> m_modelComponent = std::make_shared<ModelComponent>();

    EntityManager& m_entityManager;
};
