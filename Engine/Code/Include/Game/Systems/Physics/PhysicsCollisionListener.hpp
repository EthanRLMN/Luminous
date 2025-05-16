#pragma once

#include "LayerSystem.hpp"

#include "jolt/Jolt/Jolt.h"
#include "jolt/Jolt/Physics/PhysicsSystem.h"
#include "Logger.hpp"

#include "PhysicsSystem.hpp"


// TODO : Finish this class
class PhysicsCollisionListener final : public JPH::ContactListener
{
public:
    PhysicsCollisionListener(PhysicsSystem* manager) :
        m_physicsSystem(manager) {}

    void Init(PhysicsSystem* a_system) { m_physicsSystem = a_system; }



    inline void OnContactAdded(const JPH::Body& a_inBody1, const JPH::Body& a_inBody2, const JPH::ContactManifold& a_inManifold, JPH::ContactSettings& a_ioSettings) override
    {
        static_cast<void>(a_inManifold); static_cast<void>(a_ioSettings);

        RigidBody* l_rigidbodySource = m_physicsSystem->GetRigidBodyMap()[a_inBody1.GetID()];
        RigidBody* l_rigidbodyOther = m_physicsSystem->GetRigidBodyMap()[a_inBody2.GetID()];
        

        if (m_physicsSystem)
        {
            if (a_inBody1.IsSensor())
            {
                l_rigidbodySource->OnTriggerEnter(l_rigidbodyOther);
            } else
            {
                l_rigidbodySource->OnCollisionEnter(l_rigidbodyOther);
            }

            if (a_inBody2.IsSensor())
            {
                l_rigidbodyOther->OnTriggerEnter(l_rigidbodySource);
            } else
            {
                l_rigidbodyOther->OnCollisionEnter(l_rigidbodySource);
            }
        }

        
    }


    inline void OnContactRemoved(const JPH::SubShapeIDPair& a_inSubShapePair) override
    {
        static_cast<void>(a_inSubShapePair);
        JPH::BodyID l_body1 = a_inSubShapePair.GetBody1ID();
        JPH::BodyID l_body2 = a_inSubShapePair.GetBody2ID();

        // Notify collision exit
        RigidBody* l_rigidbodySource = m_physicsSystem->GetRigidBodyMap()[l_body1];
        RigidBody* l_rigidbodyOther = m_physicsSystem->GetRigidBodyMap()[l_body2];

        l_rigidbodySource->OnCollisionExit(l_rigidbodyOther);

    }


    inline void OnContactPersisted(const JPH::Body& a_inBody1, const JPH::Body& a_inBody2, const JPH::ContactManifold& a_inManifold, JPH::ContactSettings& a_ioSettings) override
    {

        

        static_cast<void>(a_inManifold); static_cast<void>(a_ioSettings);

        RigidBody* l_rigidbodySource = m_physicsSystem->GetRigidBodyMap()[a_inBody1.GetID()];
        RigidBody* l_rigidbodyOther = m_physicsSystem->GetRigidBodyMap()[a_inBody2.GetID()];


        if (m_physicsSystem)
        {
            if (a_inBody1.IsSensor())
            {
                l_rigidbodySource->OnTriggerExit(l_rigidbodyOther);
            } else
            {
                l_rigidbodySource->OnCollisionExit(l_rigidbodyOther);
            }

            if (a_inBody2.IsSensor())
            {
                l_rigidbodyOther->OnTriggerExit(l_rigidbodySource);
            } else
            {
                l_rigidbodyOther->OnCollisionExit(l_rigidbodySource);
            }
        }
    }


    inline JPH::ValidateResult OnContactValidate(const JPH::Body& a_inBody1, const JPH::Body& a_inBody2, JPH::RVec3Arg a_inBaseOffset, const JPH::CollideShapeResult& a_inCollisionResult) override
    {
        static_cast<void>(a_inBaseOffset); static_cast<void>(a_inCollisionResult);
        if (a_inBody1.GetObjectLayer() == Layers::DISABLED || a_inBody2.GetObjectLayer() == Layers::DISABLED)
            return JPH::ValidateResult::RejectContact;

        return JPH::ValidateResult::AcceptContact;
    }

private:
    PhysicsSystem* m_physicsSystem;

};