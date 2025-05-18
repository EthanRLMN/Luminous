#pragma once

#include <memory>
#include <vector>

#include "EntityComponent.hpp"
#include "Matrix4.hpp"
#include "Quaternion.hpp"
#include "Vector3.hpp"

class TransformComponent : public EntityComponent
{
public:
    void Initialize() override {}
    void GameplayStarted() override {}
    void Update() override {}

    Maths::Vector3 GetLocalPosition() const;
    Maths::Vector3 GetLocalScale() const;
    Maths::Vector3 GetLocalRotationVec() const;
    Maths::Quaternion GetLocalRotationQuat() const;

    Maths::Vector3 GetGlobalPosition();
    Maths::Vector3 GetGlobalScale();
    Maths::Vector3 GetGlobalRotationVec();
    Maths::Quaternion GetGlobalRotationQuat();
    Maths::Matrix4 GetLocalMatrix();
    Maths::Matrix4 GetGlobalMatrix();

    std::shared_ptr<Entity> GetParent() const;
    bool HasParent() const;
    bool HasChildren() const;
    const std::vector<std::shared_ptr<TransformComponent> >& GetChildren() const;

    std::shared_ptr<Entity> GetOwner() const override;
    void SetOwner(const std::shared_ptr<Entity>& a_relatedEntity) override;

    bool IsActive() const;
    inline void SetActive(const bool a_isActive) { m_isActive = a_isActive; }

    void SetLocalPosition(const Maths::Vector3& a_newPos);
    void SetLocalScale(const Maths::Vector3& a_newScale);
    void SetLocalRotationVec(const Maths::Vector3& a_newRotVec);
    void SetLocalRotationQuat(const Maths::Quaternion& a_newRotQuat);

    void SetGlobalPosition(const Maths::Vector3& a_newPos);
    void SetGlobalScale(const Maths::Vector3& a_newScale);
    void SetGlobalRotationVec(const Maths::Vector3& a_newRotVec);
    void SetGlobalRotationQuat(const Maths::Quaternion& a_newRotQuat);
    void SetGlobalMatrix(const Maths::Matrix4& a_newMatrix);

    void AddChild(const std::shared_ptr<TransformComponent>& a_child);
    void RemoveChild(const std::shared_ptr<TransformComponent>& a_child);
    void SetParent(const std::shared_ptr<Entity>& a_newParent);
    void SetInterpolatedRotation(const Maths::Quaternion& a_start, const Maths::Quaternion& a_end, float a_factor);


private:
    void MarkDirty();
    void UpdateGlobalTransform();
    void UpdateLocalMatrix();
    void DecomposeMatrix(const Maths::Matrix4& matrix);

    std::weak_ptr<Entity> m_parent;
    std::vector<std::shared_ptr<TransformComponent> > m_children;

    Maths::Vector3 m_localPosition{ Maths::Vector3::Zero };
    Maths::Vector3 m_localScale{ Maths::Vector3::One };
    Maths::Quaternion m_localRotationQuat{ Maths::Quaternion::Identity };
    Maths::Vector3 m_localRotationVec{ Maths::Vector3::Zero };

    Maths::Vector3 m_globalPosition{ Maths::Vector3::Zero };
    Maths::Vector3 m_globalScale{ Maths::Vector3::One };
    Maths::Quaternion m_globalRotationQuat{ Maths::Quaternion::Identity };
    Maths::Vector3 m_globalRotationVec{ Maths::Vector3::Zero };

    Maths::Matrix4 m_localMatrix{ Maths::Matrix4::identity };
    Maths::Matrix4 m_globalMatrix{ Maths::Matrix4::identity };

    bool m_requiresUpdate{ true };
    bool m_isActive{ true };
};
