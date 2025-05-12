#pragma once

#include <memory>
#include <vector>

#include "EntityComponent.hpp"
#include "Matrix4.hpp"
#include "Quaternion.hpp"
#include "Vector3.hpp"

class Entity;


class TransformComponent : public EntityComponent, std::enable_shared_from_this<TransformComponent>
{
public:
    void Initialize() override{};
    void GameplayStarted() override{};
    void Update() override{};

    [[nodiscard]] inline Maths::Vector3 GetLocalPosition() const { return m_localPosition; }
    [[nodiscard]] inline Maths::Vector3 GetLocalScale() const { return m_localScale; }
    [[nodiscard]] inline Maths::Vector3 GetLocalRotationVec() const { return m_localRotation.ToEulerAngles(true); }
    [[nodiscard]] inline Maths::Quaternion GetLocalRotationQuat() const { return m_localRotation; }
    [[nodiscard]] inline Maths::Vector3 GetGlobalPosition() const { return m_globalPosition; }
    [[nodiscard]] inline Maths::Vector3 GetGlobalScale() const { return m_globalScale; }
    [[nodiscard]] inline Maths::Vector3 GetGlobalRotationVec() const { return m_globalRotation.ToEulerAngles(true); }
    [[nodiscard]] inline Maths::Quaternion GetGlobalRotationQuat() const { return m_globalRotation; }
    [[nodiscard]] inline Maths::Matrix4 GetLocalMatrix() const { return m_localMatrix; }
    [[nodiscard]] inline Maths::Matrix4 GetGlobalMatrix() const { return m_globalMatrix; }
    [[nodiscard]] inline std::shared_ptr<Entity> GetParent() const { return m_parent.lock(); }
    [[nodiscard]] inline bool HasParent() const { return m_parent.lock() != nullptr; }
    [[nodiscard]] inline bool HasChildren() const { return !m_children.empty(); }
    [[nodiscard]] inline const std::vector<std::shared_ptr<TransformComponent>>& GetChildren() const { return m_children; }
    [[nodiscard]] inline std::shared_ptr<Entity> GetEntity() const { return m_entity.lock(); }
    [[nodiscard]] inline bool IsActive() const { return m_isActive; }

    inline void SetEntity(const std::weak_ptr<Entity>& a_relatedEntity) { m_entity = a_relatedEntity; }
    void AddChild(const std::shared_ptr<TransformComponent>& a_child);
    void RemoveChild(const std::shared_ptr<TransformComponent>& a_child);
    void SetActive(bool a_isActive);
    void SetLocalMatrix(const Maths::Matrix4& a_newMatrix);
    void SetLocalPosition(Maths::Vector3 a_newPos);
    void SetLocalScale(Maths::Vector3 a_newScale);
    void SetLocalRotationVec(Maths::Vector3 a_newRotVec);
    void SetLocalRotationQuat(Maths::Quaternion a_newRotQuat);
    void SetGlobalScale(Maths::Vector3 a_newScale);
    void SetGlobalRotationVec(Maths::Vector3 a_newRotVec);
    void SetGlobalRotationQuat(Maths::Quaternion a_newRotQuat);
    void SetGlobalMatrix(const Maths::Matrix4& a_newMatrix);
    void SetGlobalPosition(Maths::Vector3 a_newPos);
    void SetParent(const std::shared_ptr<TransformComponent>& a_newParent);
    void SetInterpolatedRotation(const Maths::Quaternion& a_start, const Maths::Quaternion& a_end, float a_factor);


private:
    std::weak_ptr<Entity> m_entity {};
    std::weak_ptr<Entity> m_parent {};
    std::vector<std::shared_ptr<TransformComponent>> m_children;

    Maths::Vector3 m_localPosition { Maths::Vector3::Zero };
    Maths::Quaternion m_localRotation { Maths::Quaternion::Identity };
    Maths::Vector3 m_localScale { Maths::Vector3::One };
    Maths::Vector3 m_globalPosition { Maths::Vector3::Zero };
    Maths::Quaternion m_globalRotation { Maths::Quaternion::Identity };
    Maths::Vector3 m_globalScale { Maths::Vector3::One };
    Maths::Matrix4 m_localMatrix { Maths::Matrix4::TRS(m_localPosition, m_localRotation.ToEulerAngles(true), m_localScale) };
    Maths::Matrix4 m_globalMatrix { Maths::Matrix4::TRS(m_globalPosition, m_globalRotation.ToEulerAngles(true), m_globalScale) };

    void UpdateGlobalTransform();
    void UpdateMatrices();
    void UpdateLocalMatrix();

    bool m_requiresUpdate { false };
    bool m_isActive { true };
};