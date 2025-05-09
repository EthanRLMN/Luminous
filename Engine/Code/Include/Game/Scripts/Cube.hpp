#pragma once

#include "Game/Systems/Component/EntityComponent.hpp"
#include "Game/Systems/Component/ModelComponent.hpp"
#include "Game/Systems/Entity/Entity.hpp"
#include "Game/Systems/Entity/EntityManager.hpp"


class Cube : public EntityComponent, public std::enable_shared_from_this<Cube>
{
public:
    explicit Cube(EntityManager& a_entityManager) : m_entityManager(a_entityManager)
    {

        m_player = a_entityManager.CreateEntity();
        m_player->SetName("Cube");
        m_player->AddComponent(m_modelComponent);
        
    }

    void Register()
    {
        m_entityManager.RegisterLogic(shared_from_this());
    }

    void Initialize() override
    {
        m_player->SetTRS(Maths::Matrix4::TRS(Maths::Vector3(-3.0f, 0.0f, 0.0f), Maths::Vector3(0.0f, 0.0f, -90.0f), Maths::Vector3::One));
        m_modelComponent->m_engine = m_engine;
        m_modelComponent->Initialize();
    }

    void GameplayStarted() override
    {
    }

    void Update() override
    {
        
    }

    std::shared_ptr<Entity> GetEntity() const
    {
        return m_player;
    }


private:
    std::shared_ptr<Entity> m_player{ nullptr };
    std::shared_ptr<ModelComponent> m_modelComponent = std::make_shared<ModelComponent>();

    EntityManager& m_entityManager;
};
