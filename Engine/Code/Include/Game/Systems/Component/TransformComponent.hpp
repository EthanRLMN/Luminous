#pragma once

#include <memory>

#include "EntityComponent.hpp"
#include "Matrix4.hpp"
#include "Quaternion.hpp"

#include "Vector3.hpp"

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
    inline Maths::Matrix4 GetModel() const { return m_modelMatrix; }
    inline std::shared_ptr<Entity> GetParent() const { return m_parent; }

    inline void SetModel(const Maths::Matrix4& a_modelMatrix) { m_modelMatrix = a_modelMatrix; }
    inline void SetLocalPosition(const Maths::Vector3 a_newPos) { m_localPosition = a_newPos; }
    inline void SetLocalScale(const Maths::Vector3 a_newScale) { m_localScale = a_newScale; }
    inline void SetLocalRotationVec(const Maths::Vector3 a_newRotVec) { m_localRotation = Maths::Quaternion::FromEulerAngles(a_newRotVec); }
    inline void SetLocalRotationQuat(const Maths::Quaternion a_newRotQuat) { m_localRotation = a_newRotQuat; }
    inline void SetGlobalPosition(const Maths::Vector3 a_newPos) { m_globalPosition = a_newPos; }
    inline void SetGlobalScale(const Maths::Vector3 a_newScale) { m_globalScale = a_newScale; }
    inline void SetGlobalRotationVec(const Maths::Vector3 a_newRotVec) { m_globalRotation = Maths::Quaternion::FromEulerAngles(a_newRotVec); }
    inline void SetGlobalRotationQuat(const Maths::Quaternion a_newRotQuat) { m_globalRotation = a_newRotQuat; }
    inline void SetParent(const std::shared_ptr<Entity>& a_newParent) { m_parent = a_newParent ; }



private:
    std::shared_ptr<Entity> m_parent { nullptr };

    Maths::Vector3 m_localPosition { Maths::Vector3::Zero };
    Maths::Quaternion m_localRotation { Maths::Quaternion::Identity };
    Maths::Vector3 m_localScale { Maths::Vector3::One };
    Maths::Vector3 m_globalPosition { Maths::Vector3::Zero };
    Maths::Quaternion m_globalRotation { Maths::Quaternion::Identity };
    Maths::Vector3 m_globalScale { Maths::Vector3::One };

    Maths::Matrix4 m_modelMatrix { Maths::Matrix4::TRS(m_localPosition, m_localRotation.ToEulerAngles(true), m_localScale) };
};
