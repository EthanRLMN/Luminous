#pragma once

#include "EntitySystem/Components/RigidbodyComponent.hpp"
#include "jolt/Jolt/Jolt.h"
#include "jolt/Jolt/Physics/PhysicsSystem.h"
#include "jolt/Jolt/Physics/Body/BodyActivationListener.h"


class CollisionSystem final : public JPH::ContactListener
{
public:
    explicit CollisionSystem(JPH::PhysicsSystem& a_physics) : m_physicsSystem(a_physics) {};

    void OnContactAdded(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override
    {

    };


private:
    using NotifyFunc = void (RigidbodyComponent::*)(std::shared_ptr<RigidbodyComponent>);

    static void HandleCollision(const JPH::Body& a_entity1, const JPH::Body& a_entity2, const NotifyFunc a_func)
    {
        // TODO : Patch
        auto l_entity1 = reinterpret_cast<RigidbodyComponent*>(l_entity1.GetUserData())->shared_from_this();;
        auto l_entity2 = reinterpret_cast<RigidbodyComponent*>(l_entity2.GetUserData())->shared_from_this();

        if (l_entity1 && l_entity2)
        {
            (*l_entity1.*a_func)(l_entity2);
            (*l_entity2.*a_func)(l_entity1);
        }
    }

    static std::shared_ptr<RigidbodyComponent> GetEntity(const JPH::Body& a_body)
    {
        return reinterpret_cast<RigidbodyComponent*>(a_body.GetUserData())->shared_from_this();
    }

    std::shared_ptr<RigidbodyComponent> GetEntity(const JPH::BodyID a_bodyId) const
    {
        const JPH::BodyLockInterfaceLocking& l_lockInterface = m_physicsSystem.GetBodyLockInterface();
        const JPH::BodyLockRead l_lock(l_lockInterface, a_bodyId);

        if (!l_lock.Succeeded())
            return nullptr;

        const JPH::Body& body = l_lock.GetBody();
        return reinterpret_cast<RigidbodyComponent*>(body.GetUserData())->shared_from_this();
    }

    JPH::PhysicsSystem& m_physicsSystem;
};












// TODO : Move out of here
class PhysicsBodyActivationListener final : public JPH::BodyActivationListener
{
public:
    virtual void OnBodyActivated(const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData) override;
    virtual void OnBodyDeactivated(const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData) override;

};