#pragma once
#include "EntitySystem/Entity.hpp"
#include "EntitySystem/EntityComponent.hpp"
#include "EntitySystem/Components/CModel.hpp"
#include "EntitySystem/Components/CRigidbody.hpp"
#include "EntitySystem/Components/CTransform.hpp"


#include "Player.hpp"

class Weapon : public EntityComponent, public std::enable_shared_from_this<Weapon>
{
public:
    Weapon(EntityManager& entityManager, std::shared_ptr<Entity> playerEntity) :
        entityManager(entityManager), m_playerEntity(playerEntity)
    {

        m_weaponEntity = entityManager.CreateEntity();
        m_weaponEntity->SetName("Weapon");



        m_weaponEntity->AddComponent(transformComponent);
        m_weaponEntity->AddComponent(modelComponent);

        modelComponent->SetModelPath("Assets/Sword.obj");
        playerEntity->AttachChild(m_weaponEntity);
        m_weaponEntity->SetParent(m_weaponEntity);
    }

    void Register()
    {
        entityManager.RegisterLogic(shared_from_this());
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
        DEBUG_LOG_INFO("Weapon Model : :{}", modelComponent->GetModelPath());
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
    std::shared_ptr<Entity> m_weaponEntity;
    std::shared_ptr<Entity> m_playerEntity;


    std::shared_ptr<TransformComponent> transformComponent = std::make_shared<TransformComponent>();
    std::shared_ptr<ModelComponent> modelComponent = std::make_shared<ModelComponent>();

    EntityManager& entityManager;
};
