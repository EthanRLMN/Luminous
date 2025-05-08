#pragma once

#include "EntitySystem/Components/ModelComponent.hpp"
#include "EntitySystem/Entity.hpp"
#include "EntitySystem/EntityComponent.hpp"
#include "EntitySystem/EntityManager.hpp"


class Player : public EntityComponent, public std::enable_shared_from_this<Player>
{
public:
    explicit Player(EntityManager& a_entityManager) :
        m_entityManager(a_entityManager)
    {

        m_player = a_entityManager.CreateEntity();
        m_player->SetName("Player");


        m_player->AddComponent(m_modelComponent);
        
    }

    void Register()
    {
        m_entityManager.RegisterLogic(shared_from_this());
    }

    void Initialize() override
    {
        m_player->SetTRS(Maths::Matrix4::TRS(Maths::Vector3::Zero, Maths::Vector3(90.f, 0.f, 90.f), Maths::Vector3::One));
        m_modelComponent.get()->m_engine = m_engine;
        m_modelComponent.get()->Initialize();
        m_modelComponent.get()->SetMesh("Engine/Assets/Models/metalSonic.obj");
        m_modelComponent.get()->SetTexture("Engine/Assets/Textures/Untitled312.png");
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
