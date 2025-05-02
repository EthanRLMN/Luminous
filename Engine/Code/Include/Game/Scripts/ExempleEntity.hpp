#pragma once
#include "EntitySystem/Entity.hpp"
#include "EntitySystem/EntityComponent.hpp"
#include "EntitySystem/Components/CTransform.hpp"
#include <iostream>


class Exemple : public EntityComponent, public std::enable_shared_from_this<Exemple>
{
public:
    Exemple(EntityManager& entityManager) :
        entityManager(entityManager)
    {

        ExempleEntity = entityManager.CreateEntity();
        
        ExempleEntity->SetName("Exemple"); 
        ExempleEntity->AddComponent(transformComponent); 
    
    }

    void Register()
    {
        entityManager.RegisterLogic(shared_from_this());
    }

    void Initialize() override 
    {
        std::cout << "[Exemple] Initialize" << std::endl;
        std::cout << "[Exemple]  Has CHild : " << ExempleEntity->HasChildren() << std::endl;
        std::cout << "[Exemple]  Has Parent : " << ExempleEntity->HasParent() << std::endl;

        transformComponent->position = { 0, 0, 0 };
        transformComponent->rotation = { 0, 0, 0 };
        transformComponent->scale = { 0, 0, 0 };
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
        return ExempleEntity;
    }


private:
    std::shared_ptr<Entity> ExempleEntity;
    EntityManager& entityManager;

    std::shared_ptr<TransformComponent> transformComponent = std::make_shared<TransformComponent>();
};
