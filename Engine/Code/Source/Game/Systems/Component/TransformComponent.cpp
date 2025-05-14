#include "Game/Systems/Component/TransformComponent.hpp"

#include <iostream>

#include "Game/Systems/Entity/Entity.hpp"


void TransformComponent::SetActive(const bool a_isActive)
{
    m_isActive = a_isActive;
    if (const std::shared_ptr<Entity> l_entity = m_entity.lock())
        l_entity->SetActive(a_isActive);

    if (m_isActive)
    {
        m_requiresUpdate = true;
        UpdateGlobalTransform();
    }
}


void TransformComponent::SetLocalMatrix(const Maths::Matrix4& a_newMatrix)
{
    if (m_localMatrix == a_newMatrix)
        return;

    m_localMatrix = a_newMatrix;
    m_requiresUpdate = true;
    UpdateGlobalTransform();
}


void TransformComponent::SetLocalPosition(const Maths::Vector3 a_newPos)
{
    if (m_localPosition == a_newPos)
        return;

    m_localPosition = a_newPos;
    m_requiresUpdate = true;
    UpdateGlobalTransform();
}


void TransformComponent::SetLocalScale(const Maths::Vector3 a_newScale)
{
    if (m_localScale == a_newScale)
        return;

    m_localScale = a_newScale;
    m_requiresUpdate = true;
    UpdateGlobalTransform();
}


void TransformComponent::SetLocalRotationVec(const Maths::Vector3 a_newRotVec)
{
    if (m_localRotation.ToEulerAngles(true) == a_newRotVec)
        return;

    m_localRotation = Maths::Quaternion::FromEulerAngles(a_newRotVec);
    m_requiresUpdate = true;
    UpdateGlobalTransform();
}


void TransformComponent::SetLocalRotationQuat(const Maths::Quaternion a_newRotQuat)
{
    if (m_localRotation == a_newRotQuat)
        return;

    m_localRotation = a_newRotQuat;
    m_requiresUpdate = true;
    UpdateGlobalTransform();
}


void TransformComponent::SetGlobalScale(const Maths::Vector3 a_newScale)
{
    if (m_globalScale == a_newScale)
        return;

    m_globalScale = a_newScale;
    m_requiresUpdate = true;
    UpdateGlobalTransform();
}


void TransformComponent::SetGlobalRotationVec(const Maths::Vector3 a_newRotVec)
{
    if (m_globalRotation.ToEulerAngles(true) == a_newRotVec)
        return;

    m_globalRotation = Maths::Quaternion::FromEulerAngles(a_newRotVec);
    m_requiresUpdate = true;
    UpdateGlobalTransform();
}


void TransformComponent::SetGlobalRotationQuat(const Maths::Quaternion a_newRotQuat)
{
    if (m_globalRotation == a_newRotQuat)
        return;

    m_globalRotation = a_newRotQuat;
    m_requiresUpdate = true;
    UpdateGlobalTransform();
}


void TransformComponent::SetGlobalMatrix(const Maths::Matrix4& a_newMatrix)
{
    m_globalMatrix = a_newMatrix;
    m_globalPosition = a_newMatrix.GetTranslation();
    m_globalRotation = Maths::Quaternion::FromMatrix(a_newMatrix);
    m_globalScale    = a_newMatrix.GetScale();

    if (m_parent.lock())
    {
        const std::shared_ptr<TransformComponent> l_parentTransform = m_parent.lock()->Transform();
        if (l_parentTransform)
        {
            const Maths::Matrix4 l_inverseParent = l_parentTransform->GetGlobalMatrix().Inverse();
            m_localMatrix = l_inverseParent * m_globalMatrix;
            m_localPosition = m_localMatrix.GetTranslation();
            m_localRotation = Maths::Quaternion::FromMatrix(m_localMatrix);
            m_localScale    = m_localMatrix.GetScale();
        }
    }
    else
    {
        m_localMatrix = m_globalMatrix;
        m_localPosition = m_globalPosition;
        m_localRotation = m_globalRotation;
        m_localScale    = m_globalScale;
    }
    UpdateMatrices();
}


void TransformComponent::SetGlobalPosition(const Maths::Vector3 a_newPos)
{
    if (m_globalPosition == a_newPos)
        return;

    m_globalPosition = a_newPos;
    if (m_parent.lock())
    {
        const Maths::Matrix4 l_parentGlobalInverse = m_parent.lock()->Transform()->GetGlobalMatrix().Inverse();
        m_localMatrix = l_parentGlobalInverse * Maths::Matrix4::TRS(a_newPos, m_globalRotationVec, m_globalScale);
    }

    SetLocalPosition(a_newPos);
}


void TransformComponent::SetParent(const std::shared_ptr<Entity>& a_newParent)
{
    if (m_parent.lock() != a_newParent)
    {
        std::shared_ptr<TransformComponent> l_tempParent = a_newParent->Transform();
        while (l_tempParent)
        {
            if (l_tempParent == shared_from_this())
                return;

            l_tempParent = l_tempParent->GetParent()->Transform();
        }

        if (m_parent.lock())
        {
            const std::shared_ptr<TransformComponent> l_oldParentTransform = m_parent.lock()->Transform();
            if (l_oldParentTransform)
                l_oldParentTransform->RemoveChild(m_parent.lock()->Transform());
        }

        m_parent = a_newParent;
        UpdateGlobalTransform();

        if (m_parent.lock())
        {
            const std::shared_ptr<TransformComponent> l_newParentTransform = m_parent.lock()->Transform();
            if (l_newParentTransform)
                l_newParentTransform->AddChild(std::shared_ptr<TransformComponent>(this));
        }
    }
}


void TransformComponent::SetInterpolatedRotation(const Maths::Quaternion& a_start, const Maths::Quaternion& a_end, const float a_factor)
{
    m_localRotation = Maths::Quaternion::Slerp(a_start, a_end, a_factor);
    m_requiresUpdate = true;
    UpdateGlobalTransform();
}


void TransformComponent::UpdateGlobalTransform()
{
    if (!m_requiresUpdate || !m_entity.lock() || m_entity.lock() == nullptr || !m_entity.lock()->IsActive())
        return;

    UpdateLocalMatrix();

    if (m_parent.lock())
    {
        const std::shared_ptr<TransformComponent> l_parentTransform = m_parent.lock()->Transform();
        if (l_parentTransform)
            m_globalMatrix = l_parentTransform->GetGlobalMatrix() * m_localMatrix;
        else
            m_globalMatrix = m_localMatrix;
    }
    else
        m_globalMatrix = m_localMatrix;

    m_globalMatrix.Decompose(m_globalPosition, m_globalRotation, m_globalScale);

    m_requiresUpdate = false;
    for (const std::shared_ptr<TransformComponent>& l_child : m_children)
        l_child->UpdateMatrices();
}


void TransformComponent::UpdateMatrices()
{
    UpdateLocalMatrix();

    if (m_parent.lock())
    {
        const std::shared_ptr<TransformComponent> l_parentTransform = m_parent.lock()->Transform();
        if (l_parentTransform)
            m_globalMatrix = l_parentTransform->GetGlobalMatrix() * m_localMatrix;
    }
    else
        m_globalMatrix = m_localMatrix;

    m_globalPosition = m_globalMatrix.GetTranslation();
    m_globalRotation = Maths::Quaternion::FromMatrix(m_globalMatrix);
    m_globalScale = m_globalMatrix.GetScale();

    for (const std::shared_ptr<TransformComponent>& l_child : m_children)
        if (l_child)
            l_child->UpdateMatrices();
}


void TransformComponent::UpdateLocalMatrix()
{
    m_localMatrix = Maths::Matrix4::TRS(m_localPosition, m_localRotation.ToEulerAngles(true), m_localScale);
}
