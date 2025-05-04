#pragma once

#include <iostream>

#include "EntitySystem/Entity.hpp"
#include "EntitySystem/EntityComponent.hpp"
#include "EntitySystem/EntityManager.hpp"
#include "EntitySystem/Components/TransformComponent.hpp"


class Example : public EntityComponent, public std::enable_shared_from_this<Example>
{
public:
    explicit Example(EntityManager& entityManager) : m_entityManager(entityManager)
    {

        m_exampleEntity = entityManager.CreateEntity();
        
        m_exampleEntity->SetName("Exemple");
        m_exampleEntity->AddComponent(m_transformComponent);
    }


    void Register()
    {
        m_entityManager.RegisterLogic(shared_from_this());
    }


    void Initialize() override 
    {
        std::cout << "[Exemple] Initialize" << std::endl;
        std::cout << "[Exemple]  Has CHild : " << m_exampleEntity->HasChildren() << std::endl;
        std::cout << "[Exemple]  Has Parent : " << m_exampleEntity->HasParent() << std::endl;

        m_transformComponent->position = Maths::Vector3{ 0.f, 0.f, 0.f };
        m_transformComponent->rotation = Maths::Quaternion{ 0.f, 0.f, 0.f, 0.f};
        m_transformComponent->scale = Maths::Vector3{ 0.f, 0.f, 0.f };
    }


    void GameplayStarted() override 
    {
        std::cout << "[Exemple] Gameplay Started" << std::endl;

    }


    void Update() override 
    {
        std::cout << "[Exemple] Update Tick" << std::endl;
    }


    std::shared_ptr<Entity> GetEntity() const
    {
        return m_exampleEntity;
    }


private:
    std::shared_ptr<Entity> m_exampleEntity { nullptr };
    EntityManager& m_entityManager;

    std::shared_ptr<TransformComponent> m_transformComponent = std::make_shared<TransformComponent>();
};
