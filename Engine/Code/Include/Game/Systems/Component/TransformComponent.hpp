#pragma once

#include <memory>

#include "EntityComponent.hpp"
#include "Matrix4.hpp"
#include "Quaternion.hpp"

#include "Vector3.hpp"
#include "Game/Systems/Entity/Entity.hpp"

class Entity;

class TransformComponent : public EntityComponent
{
public:
    void Initialize() override{};
    void GameplayStarted() override{};
    void Update() override{};

    inline Maths::Vector3 GetLocalPosition() const { return m_localPosition; }
    inline Maths::Vector3 GetLocalScale() const { return m_localScale; }
    inline Maths::Vector3 GetLocalRotationVec() const { return m_localRotation.ToEulerAngles(true); }
    inline Maths::Quaternion GetLocalRotationQuat() const { return m_localRotation; }
    inline Maths::Vector3 GetGlobalPosition() const { return m_globalPosition; }
    inline Maths::Vector3 GetGlobalScale() const { return m_globalScale; }
    inline Maths::Vector3 GetGlobalRotationVec() const { return m_globalRotation.ToEulerAngles(true); }
    inline Maths::Quaternion GetGlobalRotationQuat() const { return m_globalRotation; }
    inline Maths::Matrix4 GetLocalMatrix() const { return m_localMatrix; }
    inline Maths::Matrix4 GetGlobalMatrix() const { return m_globalMatrix; }
    inline std::shared_ptr<Entity> GetParent() const { return m_parent; }

    inline void SetLocalMatrix(const Maths::Matrix4& a_newMatrix) { m_localMatrix = a_newMatrix; }
    inline void SetGlobalMatrix(const Maths::Matrix4& a_newMatrix) { m_globalMatrix = a_newMatrix; }
    inline void SetLocalPosition(const Maths::Vector3 a_newPos) { m_localPosition = a_newPos; }
    inline void SetLocalScale(const Maths::Vector3 a_newScale) { m_localScale = a_newScale; }
    inline void SetLocalRotationVec(const Maths::Vector3 a_newRotVec) { m_localRotation = Maths::Quaternion::FromEulerAngles(a_newRotVec); }
    inline void SetLocalRotationQuat(const Maths::Quaternion a_newRotQuat) { m_localRotation = a_newRotQuat; }
    inline void SetGlobalPosition(const Maths::Vector3 a_newPos) { m_globalPosition = a_newPos; }
    inline void SetGlobalScale(const Maths::Vector3 a_newScale) { m_globalScale = a_newScale; }
    inline void SetGlobalRotationVec(const Maths::Vector3 a_newRotVec) { m_globalRotation = Maths::Quaternion::FromEulerAngles(a_newRotVec); }
    inline void SetGlobalRotationQuat(const Maths::Quaternion a_newRotQuat) { m_globalRotation = a_newRotQuat; }

    inline void SetParent(const std::shared_ptr<Entity>& a_newParent)
    {
        m_parent = a_newParent;
        UpdateGlobalTransform();
    }


private:
    std::shared_ptr<Entity> m_parent { nullptr };

    Maths::Vector3 m_localPosition { Maths::Vector3::Zero };
    Maths::Quaternion m_localRotation { Maths::Quaternion::Identity };
    Maths::Vector3 m_localScale { Maths::Vector3::One };
    Maths::Vector3 m_globalPosition { Maths::Vector3::Zero };
    Maths::Quaternion m_globalRotation { Maths::Quaternion::Identity };
    Maths::Vector3 m_globalScale { Maths::Vector3::One };

    Maths::Matrix4 m_localMatrix { Maths::Matrix4::TRS(m_localPosition, m_localRotation.ToEulerAngles(true), m_localScale) };
    Maths::Matrix4 m_globalMatrix { Maths::Matrix4::TRS(m_globalPosition, m_globalRotation.ToEulerAngles(true), m_globalScale) };

    inline void UpdateGlobalTransform()
    {
        m_localMatrix = Maths::Matrix4::TRS(m_localPosition, m_localRotation.ToEulerAngles(true), m_localScale);

        if (m_parent)
        {
            const std::shared_ptr<TransformComponent> l_parentTransform = m_parent->GetComponent<TransformComponent>();
            if (l_parentTransform)
                m_globalMatrix = l_parentTransform->GetGlobalMatrix() * m_localMatrix;
            else
                m_globalMatrix = m_localMatrix;
        }
        else
            m_globalMatrix = m_localMatrix;
    }
};
