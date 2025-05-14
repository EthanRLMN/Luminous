#include <algorithm>

#include "Game/Systems/Component/TransformComponent.hpp"
#include "Game/Systems/Entity/Entity.hpp"


void TransformComponent::AddChild(const std::shared_ptr<TransformComponent>& a_child) const
{
    if (a_child)
        a_child->SetParent(GetOwner());
}


void TransformComponent::RemoveChild(const std::shared_ptr<TransformComponent>& a_child)
{
    const auto it = std::ranges::find(m_children, a_child); // Use auto because we can't deduce the type of the iterator
    if (it != m_children.end())
        m_children.erase(it);
}


void TransformComponent::SetActive(const bool a_isActive)
{
    m_isActive = a_isActive;
    if (const std::shared_ptr<Entity> l_entity = p_owner)
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
    if (m_localRotationVec == a_newRotVec)
        return;

    m_localRotationVec = a_newRotVec;
    m_requiresUpdate = true;
    UpdateGlobalTransform();
}


void TransformComponent::SetLocalRotationQuat(const Maths::Quaternion a_newRotQuat)
{
    if (m_localRotationQuat == a_newRotQuat)
        return;

    m_localRotationQuat = a_newRotQuat;
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
    if (m_globalRotationVec == a_newRotVec)
        return;

    m_globalRotationQuat = Maths::Quaternion::FromEulerAngles(a_newRotVec);
    m_requiresUpdate = true;
    UpdateGlobalTransform();
}


void TransformComponent::SetGlobalRotationQuat(const Maths::Quaternion a_newRotQuat)
{
    if (m_globalRotationQuat == a_newRotQuat)
        return;

    m_globalRotationQuat = a_newRotQuat;
    m_requiresUpdate = true;
    UpdateGlobalTransform();
}


void TransformComponent::SetGlobalMatrix(const Maths::Matrix4& a_newMatrix)
{
    m_globalMatrix = a_newMatrix;
    m_globalPosition = a_newMatrix.GetTranslation();
    m_globalRotationQuat = Maths::Quaternion::FromMatrix(a_newMatrix);
    m_globalScale    = a_newMatrix.GetScale();

    if (m_parent.lock())
    {
        const std::shared_ptr<TransformComponent> l_parentTransform = m_parent.lock()->Transform();
        if (l_parentTransform)
        {
            const Maths::Matrix4 l_inverseParent = l_parentTransform->GetGlobalMatrix().Inverse();
            m_localMatrix = l_inverseParent * m_globalMatrix;
            m_localPosition = m_localMatrix.GetTranslation();
            m_localRotationQuat = Maths::Quaternion::FromMatrix(m_localMatrix);
            m_localScale    = m_localMatrix.GetScale();
        }
    }
    else
    {
        m_localMatrix = m_globalMatrix;
        m_localPosition = m_globalPosition;
        m_localRotationQuat = m_globalRotationQuat;
        m_localScale    = m_globalScale;
    }
    UpdateMatrices();
}


void TransformComponent::SetGlobalPosition(const Maths::Vector3 a_newPos)
{
    m_globalPosition = a_newPos;

    if (m_parent.lock())
    {
        const Maths::Matrix4 l_parentGlobalInverse = m_parent.lock()->Transform()->GetGlobalMatrix().Inverse();
        m_localMatrix = l_parentGlobalInverse * Maths::Matrix4::TRS(a_newPos, m_globalRotationVec, m_globalScale);
    }
    else
        m_localMatrix = Maths::Matrix4::TRS(a_newPos, m_globalRotationVec, m_globalScale);

    UpdateGlobalTransform();
}


void TransformComponent::SetParent(const std::shared_ptr<Entity>& a_newParent)
{
    if (m_parent.lock() == a_newParent)
        return;

    std::shared_ptr<TransformComponent> l_tempParent = a_newParent ? a_newParent->Transform() : nullptr;
    while (l_tempParent)
    {
        if (l_tempParent.get() == this)
            return;

        const std::shared_ptr<Entity> l_tempEntity = l_tempParent->GetParent();
        l_tempParent = l_tempEntity ? l_tempEntity->Transform() : nullptr;
    }
    if (const std::shared_ptr<Entity> l_oldParentEntity = m_parent.lock())
    {
        if (const std::shared_ptr<TransformComponent> l_oldTransform = l_oldParentEntity->Transform())
        {
            std::vector<std::shared_ptr<TransformComponent>>& children = l_oldTransform->m_children;
            std::erase_if(children, [this](const std::shared_ptr<TransformComponent>& child) { return child.get() == this; });
        }
    }

    m_parent = a_newParent;

    if (a_newParent)
    {
        const std::shared_ptr<TransformComponent> l_newParentTransform = a_newParent->Transform();
        if (l_newParentTransform)
            l_newParentTransform->m_children.push_back(GetOwner()->Transform());
    }

    UpdateGlobalTransform();
}


void TransformComponent::SetInterpolatedRotation(const Maths::Quaternion& a_start, const Maths::Quaternion& a_end, const float a_factor)
{
    m_localRotationQuat = Maths::Quaternion::Slerp(a_start, a_end, a_factor);
    m_requiresUpdate = true;
    UpdateGlobalTransform();
}


void TransformComponent::UpdateGlobalTransform()
{
    if (!m_requiresUpdate || !p_owner || p_owner == nullptr || !p_owner->IsActive())
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

    m_globalMatrix.Decompose(m_globalPosition, m_globalRotationQuat, m_globalScale);

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
    m_globalRotationQuat = Maths::Quaternion::FromMatrix(m_globalMatrix);
    m_globalScale = m_globalMatrix.GetScale();

    for (const std::shared_ptr<TransformComponent>& l_child : m_children)
        if (l_child)
            l_child->UpdateMatrices();
}


void TransformComponent::UpdateLocalMatrix()
{
    m_localMatrix = Maths::Matrix4::TRS(m_localPosition, m_localRotationVec, m_localScale);
}
