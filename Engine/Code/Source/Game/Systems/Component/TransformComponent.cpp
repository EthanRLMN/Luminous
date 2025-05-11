#include "Game/Systems/Component/TransformComponent.hpp"
#include "Game/Systems/Entity/Entity.hpp"

void TransformComponent::SetParent(const std::shared_ptr<Entity>& a_newParent)
{
    if (m_parent != a_newParent)
    {
        if (m_parent)
        {
            const std::shared_ptr<TransformComponent> l_oldParentTransform = m_parent->Transform();
            if (l_oldParentTransform)
                l_oldParentTransform->RemoveChild(m_parent->Transform());
        }

        m_parent = a_newParent;
        UpdateGlobalTransform();

        if (m_parent)
        {
            const std::shared_ptr<TransformComponent> l_newParentTransform = m_parent->Transform();
            if (l_newParentTransform)
                l_newParentTransform->AddChild(std::shared_ptr<TransformComponent>(this));
        }
    }
}


void TransformComponent::UpdateGlobalTransform()
{
    m_localMatrix = Maths::Matrix4::TRS(m_localPosition, m_localRotation.ToEulerAngles(true), m_localScale);

    if (m_parent)
    {
        const std::shared_ptr<TransformComponent> l_parentTransform = m_parent->Transform();
        if (l_parentTransform)
            m_globalMatrix = l_parentTransform->GetGlobalMatrix() * m_localMatrix;
        else
            m_globalMatrix = m_localMatrix;
    } else
        m_globalMatrix = m_localMatrix;

    m_globalMatrix.Decompose(m_globalPosition, m_globalRotation, m_globalScale);

    for (const std::shared_ptr<TransformComponent>& l_child : m_children)
        l_child->UpdateGlobalTransform();
}
