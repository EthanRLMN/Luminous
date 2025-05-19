
#pragma once
#include "BaseScript.hpp"
#include "Game/Systems/Component/RigidbodyComponent.hpp"

class PlayerScript : public BaseScript
{

    float m_speed = 0.1f;
    std::shared_ptr<TransformComponent>  m_transform;
    bool bJumpCD = false;


    void HandleRotate(IInputManager* a_input)
    {
        const Maths::Vector2 l_mouseDelta{ a_input->GetMouseDelta() };

        std::shared_ptr<TransformComponent> l_child = m_transform->GetChildren()[0];
        Maths::Vector3 newRot = l_child->GetGlobalRotationVec() + Maths::Vector3(std::clamp(l_mouseDelta.y * -0.25f, -89.0f, 89.0f), l_mouseDelta.x * 0.25f, 0.f);
        l_child->SetGlobalRotationVec(newRot);

    }

    void HandleMovement(IInputManager* a_input)
    {
        if (a_input->IsKeyDown(Key::KEY_W))
        {
            std::shared_ptr<TransformComponent> l_child = m_transform->GetChildren()[0];

            //m_owner->GetEngine()->GetPhysicsSystem()->GetBodyInterface().ActivateBody(m_owner->GetComponent<RigidbodyComponent>()->GetRigidbody()->GetRigidBody()->GetID());
            //m_owner->GetEngine()->GetPhysicsSystem()->GetBodyInterface().AddImpulse(m_owner->GetComponent<RigidbodyComponent>()->GetRigidbody()->GetRigidBody()->GetID(), JPH::Vec3(0, 0.f, -100000.f) * m_speed);
            m_owner->GetEngine()->GetPhysicsSystem()->GetBodyInterface().SetPosition(m_owner->GetComponent<RigidbodyComponent>()->GetRigidbody()->GetRigidBody()->GetID(), m_owner->GetComponent<RigidbodyComponent>()->GetRigidbody()->GetRigidBody()->GetPosition() + JPH::Vec3(0.f, 0.f, -1.f) * m_speed, m_owner->GetComponent<RigidbodyComponent>()->GetActivation());
        }

        if (a_input->IsKeyDown(Key::KEY_S))
        {
            //m_transform->SetGlobalPosition(m_transform->GetGlobalPosition() + Maths::Vector3(0.f, 0.f, -1.0f) * m_speed);
            m_owner->GetEngine()->GetPhysicsSystem()->GetBodyInterface().SetPosition(m_owner->GetComponent<RigidbodyComponent>()->GetRigidbody()->GetRigidBody()->GetID(), m_owner->GetComponent<RigidbodyComponent>()->GetRigidbody()->GetRigidBody()->GetPosition() + JPH::Vec3(0.f, 0.f, 1.f) * m_speed, m_owner->GetComponent<RigidbodyComponent>()->GetActivation());
        }

        if (a_input->IsKeyDown(Key::KEY_A))
        {
            m_owner->GetEngine()->GetPhysicsSystem()->GetBodyInterface().SetPosition(m_owner->GetComponent<RigidbodyComponent>()->GetRigidbody()->GetRigidBody()->GetID(), m_owner->GetComponent<RigidbodyComponent>()->GetRigidbody()->GetRigidBody()->GetPosition() + JPH::Vec3(-1.f, 0.f, 0.f) * m_speed, m_owner->GetComponent<RigidbodyComponent>()->GetActivation());
        }

        if (a_input->IsKeyDown(Key::KEY_D))
        {
            m_owner->GetEngine()->GetPhysicsSystem()->GetBodyInterface().SetPosition(m_owner->GetComponent<RigidbodyComponent>()->GetRigidbody()->GetRigidBody()->GetID(), m_owner->GetComponent<RigidbodyComponent>()->GetRigidbody()->GetRigidBody()->GetPosition() + JPH::Vec3(1.f, 0.f, 0.f) * m_speed, m_owner->GetComponent<RigidbodyComponent>()->GetActivation());
        }
    }

    void HandleJump(IInputManager* a_input)
    {
        if (a_input->IsKeyPressed(Key::KEY_SPACE) && bJumpCD == false)
        {
            bJumpCD = true;
            m_owner->GetEngine()->GetPhysicsSystem()->GetBodyInterface().ActivateBody(m_owner->GetComponent<RigidbodyComponent>()->GetRigidbody()->GetRigidBody()->GetID());
            m_owner->GetEngine()->GetPhysicsSystem()->GetBodyInterface().AddImpulse(m_owner->GetComponent<RigidbodyComponent>()->GetRigidbody()->GetRigidBody()->GetID(), JPH::Vec3(0, 100000.f, 0) * 3); 
            
        }

        if (a_input->IsKeyReleased(Key::KEY_SPACE))
        {
            bJumpCD = false;
        }
    }

    void Init() override
    {
        m_transform = m_owner->Transform();
    };
    void Update() override
    {
        IInputManager* l_input = m_owner->GetEngine()->GetInputManager();
        HandleMovement(l_input);
        HandleJump(l_input);
        HandleRotate(l_input);
    };
};
