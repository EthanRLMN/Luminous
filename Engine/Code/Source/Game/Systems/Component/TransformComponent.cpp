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

    m_localPosition     = m_localMatrix.GetTranslation();
    m_localRotationQuat = Maths::Quaternion::FromMatrix(m_localMatrix);
    m_localRotationVec  = m_localRotationQuat.ToEulerAngles(true);
    m_localScale        = m_localMatrix.GetScale();

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
    m_localRotationQuat = Maths::Quaternion::FromEulerAngles(a_newRotVec);
    m_requiresUpdate = true;
    UpdateGlobalTransform();
}


void TransformComponent::SetLocalRotationQuat(const Maths::Quaternion a_newRotQuat)
{
    if (m_localRotationQuat == a_newRotQuat)
        return;

    m_localRotationQuat = a_newRotQuat;
    m_localRotationVec  = m_localRotationQuat.ToEulerAngles(true);
    m_requiresUpdate = true;
    UpdateGlobalTransform();
}


void TransformComponent::SetGlobalScale(const Maths::Vector3 a_newScale)
{
    if (m_globalScale == a_newScale)
        return;

    SetGlobalMatrix(Maths::Matrix4::TRS(m_globalPosition, m_globalRotationQuat, a_newScale));
}


void TransformComponent::SetGlobalRotationVec(const Maths::Vector3 a_newRotVec)
{
    SetGlobalRotationQuat(Maths::Quaternion::FromEulerAngles(a_newRotVec));
}


void TransformComponent::SetGlobalRotationQuat(const Maths::Quaternion a_newRotQuat)
{
    if (m_globalRotationQuat == a_newRotQuat)
        return;

    SetGlobalMatrix(Maths::Matrix4::TRS(m_globalPosition, a_newRotQuat, m_globalScale));
}


void TransformComponent::SetGlobalMatrix(const Maths::Matrix4& a_newMatrix)
{
    m_globalMatrix     = a_newMatrix;
    m_globalPosition   = a_newMatrix.GetTranslation();
    m_globalRotationQuat = Maths::Quaternion::FromMatrix(a_newMatrix);
    m_globalRotationVec  = m_globalRotationQuat.ToEulerAngles(true);
    m_globalScale      = a_newMatrix.GetScale();

    if (const std::shared_ptr<Entity> l_parent = m_parent.lock())
    {
        const std::shared_ptr<TransformComponent> l_parentTransform = l_parent->Transform();
        if (l_parentTransform)
            m_localMatrix = l_parentTransform->GetGlobalMatrix().Inverse() * m_globalMatrix;
        else
            m_localMatrix = m_globalMatrix;
    }
    else
        m_localMatrix = m_globalMatrix;

    m_localPosition     = m_localMatrix.GetTranslation();
    m_localRotationQuat = Maths::Quaternion::FromMatrix(m_localMatrix);
    m_localRotationVec  = m_localRotationQuat.ToEulerAngles(true);
    m_localScale        = m_localMatrix.GetScale();

    UpdateMatrices();
}


void TransformComponent::SetGlobalPosition(const Maths::Vector3 a_newPos)
{
    if (m_globalPosition == a_newPos)
        return;

    SetGlobalMatrix(Maths::Matrix4::TRS(a_newPos, m_globalRotationQuat, m_globalScale));
}


void TransformComponent::SetParent(const std::shared_ptr<Entity>& a_newParent)
{
    if (m_parent.lock() == a_newParent)
        return;

    const Maths::Matrix4 l_oldGlobal = GetGlobalMatrix();

    if (const std::shared_ptr<Entity> l_oldParent = m_parent.lock())
        if (const std::shared_ptr<TransformComponent> l_transform = l_oldParent->Transform())
            std::erase_if(l_transform->m_children,
                         [this](auto& c){ return c.get() == this; });

    m_parent = a_newParent;
    if (const std::shared_ptr<TransformComponent> l_newTransform = a_newParent ? a_newParent->Transform() : nullptr)
    {
        l_newTransform->m_children.push_back(GetOwner()->Transform());
        m_localMatrix = l_newTransform->GetGlobalMatrix().Inverse() * l_oldGlobal;
    }
    else
        m_localMatrix = l_oldGlobal;

    m_localPosition     = m_localMatrix.GetTranslation();
    m_localRotationQuat = Maths::Quaternion::FromMatrix(m_localMatrix);
    m_localRotationVec  = m_localRotationQuat.ToEulerAngles(true);
    m_localScale        = m_localMatrix.GetScale();

    SetGlobalMatrix(l_oldGlobal);
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
    m_globalRotationVec = m_globalRotationQuat.ToEulerAngles(true);

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
    m_localMatrix = Maths::Matrix4::TRS(m_localPosition, m_localRotationQuat, m_localScale);
}
