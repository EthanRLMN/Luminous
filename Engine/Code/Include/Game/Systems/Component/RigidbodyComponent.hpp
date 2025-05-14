#pragma once
#include <memory>
#include <vector>

#include "Game/Systems/Physics/PhysicsCollisionListener.hpp"
#include "Game/Systems/Component/ModelComponent.hpp"
#include "Game/Systems/Physics/RigidBody.hpp"
#include "Game/Systems/Physics/LayerSystem.hpp"


enum ColliderType
{
    BOXCOLLIDER = 0,
    SPHERECOLLIDER = 1,
    CAPSULECOLLIDER = 2
};

class RigidbodyComponent : public EntityComponent
{
public:
    ~RigidbodyComponent() override = default;
    void Initialize() override;
    void GameplayStarted() override{};
    void Update() override{};

    [[nodiscard]] inline std::shared_ptr<Entity> GetEntity() const { return m_entity.lock(); }
    inline void SetEntity(const std::weak_ptr<Entity>& a_relatedEntity) { m_entity = a_relatedEntity; }

    ModelComponent* GetModelDebug() { return m_collisionDebugModel; }
    void SetLayer(JPH::uint8 a_layer) { m_layer = a_layer; }

    JPH::EActivation m_active = JPH::EActivation::Activate;

private:
    JPH::uint8 m_layer = Layers::KINEMATIC;
    std::weak_ptr<Entity> m_entity{};
    ModelComponent* m_collisionDebugModel;
    RigidBody* m_rigidbody;
    ColliderType m_colliderType = ColliderType::CAPSULECOLLIDER;
};


/*
class RigidbodyComponent : public std::enable_shared_from_this<RigidbodyComponent>
{
public:
    inline void AddCollisionListener(const std::shared_ptr<ICollisionListener>& a_listener) { m_listeners.push_back(a_listener); }

    void NotifyCollisionEnter(const std::shared_ptr<RigidbodyComponent>& a_other)
    {
        for (const std::shared_ptr<ICollisionListener>& l_listener : m_listeners)
            l_listener->OnCollisionEnter(shared_from_this(), a_other);
    }

    void NotifyCollisionStay(const std::shared_ptr<RigidbodyComponent>& a_other)
    {
        for (const std::shared_ptr<ICollisionListener>& l_listener : m_listeners)
            l_listener->OnCollisionStay(shared_from_this(), a_other);
    }

    void NotifyCollisionExit(const std::shared_ptr<RigidbodyComponent>& a_other)
    {
        for (const std::shared_ptr<PhysicsCollisionListener>& l_listener : m_listeners)
            l_listener->OnColl(shared_from_this(), a_other);
    }


    bool IsSimulatingPhysics() const { return m_simulatePhysics; }
    void SetSimulatingPhysics(const bool a_value) { m_simulatePhysics = a_value; }


private:
    std::vector<std::shared_ptr<ICollisionListener>> m_listeners { };
    bool m_simulatePhysics { true };
};
*/