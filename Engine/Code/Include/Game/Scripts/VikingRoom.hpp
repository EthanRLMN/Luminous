#pragma once

#include "Game/Systems/Component/EntityComponent.hpp"
#include "Game/Systems/Component/ModelComponent.hpp"
#include "Game/Systems/Entity/Entity.hpp"
#include "Game/Systems/Entity/EntityManager.hpp"

class VikingRoom : public EntityComponent, public std::enable_shared_from_this<VikingRoom>
{
public:
    explicit VikingRoom(EntityManager& a_entityManager) :
        m_entityManager(a_entityManager)
    {
        m_vikingroom = a_entityManager.CreateEntity();
        m_vikingroom->SetName("PlayerModel");
        m_vikingroom->AddComponent(m_modelComponent);
    }

    void Register()
    {
        m_entityManager.RegisterLogic(shared_from_this());
    }

    void Initialize() override
    {
        m_vikingroom->SetTRS(Maths::Matrix4::TRS(Maths::Vector3(5.0f, 0.f, 0.f), Maths::Vector3(0.f, 0.f, 0.f), Maths::Vector3::One));
        m_modelComponent->m_engine = m_engine;
        m_modelComponent->Initialize();
        m_modelComponent->SetMesh("Engine/Assets/Default/Models/viking_room.obj");
        m_modelComponent->SetTexture("Engine/Assets/Default/Textures/viking_room.png");
    }

    void GameplayStarted() override {}
    void Update() override{}

    std::shared_ptr<Entity> GetEntity() const{ return m_vikingroom;}


private:
    std::shared_ptr<Entity> m_vikingroom{ nullptr };
    std::shared_ptr<ModelComponent> m_modelComponent = std::make_shared<ModelComponent>();

    EntityManager& m_entityManager;
};
