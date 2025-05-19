#include "Game/Systems/Component/TransformComponent.hpp"

#include "Game/Systems/Entity/Entity.hpp"

using namespace Maths;

Vector3 TransformComponent::GetLocalPosition() const { return m_localPosition; }
Vector3 TransformComponent::GetLocalScale() const { return m_localScale; }
Vector3 TransformComponent::GetLocalRotationVec() const { return m_localRotationVec; }
Quaternion TransformComponent::GetLocalRotationQuat() const { return m_localRotationQuat; }

Vector3 TransformComponent::GetGlobalPosition()
{
    UpdateGlobalTransform();
    return m_globalPosition;
}

Vector3 TransformComponent::GetGlobalScale()
{
    UpdateGlobalTransform();
    return m_globalScale;
}

Vector3 TransformComponent::GetGlobalRotationVec()
{
    UpdateGlobalTransform();
    return m_globalRotationVec;
}

Quaternion TransformComponent::GetGlobalRotationQuat()
{
    UpdateGlobalTransform();
    return m_globalRotationQuat;
}

Matrix4 TransformComponent::GetLocalMatrix()
{
    UpdateLocalMatrix();
    return m_localMatrix;
}

Matrix4 TransformComponent::GetGlobalMatrix()
{
    UpdateGlobalTransform();
    return m_globalMatrix;
}


std::shared_ptr<Entity> TransformComponent::GetParent() const { return m_parent.lock(); }
bool TransformComponent::HasParent() const { return !m_parent.expired(); }
bool TransformComponent::HasChildren() const { return !m_children.empty(); }
const std::vector<std::shared_ptr<TransformComponent> >& TransformComponent::GetChildren() const { return m_children; }
std::shared_ptr<Entity> TransformComponent::GetOwner() const { return p_owner; }
void TransformComponent::SetOwner(const std::shared_ptr<Entity>& a_relatedEntity) { p_owner = a_relatedEntity; }
bool TransformComponent::IsActive() const { return m_isActive; }
void TransformComponent::SetActive(const bool a_isActive) { m_isActive = a_isActive; }


void TransformComponent::MarkDirty()
{
    m_requiresUpdate = true;
    for (std::shared_ptr<TransformComponent>& child : m_children)
    {
        if (child)
            child->MarkDirty();
    }
}


void TransformComponent::UpdateLocalMatrix()
{
    m_localMatrix = Matrix4::TRS(m_localPosition, m_localRotationQuat, m_localScale);
}


void TransformComponent::DecomposeMatrix(const Matrix4& matrix)
{
    matrix.Decompose(m_globalPosition, m_globalRotationQuat, m_globalScale);
    m_globalRotationVec = m_globalRotationQuat.ToEulerAngles(true);
}

void TransformComponent::UpdateGlobalTransform()
{
    if (!m_requiresUpdate)
        return;

    UpdateLocalMatrix();

    const std::shared_ptr<Entity> l_parent = m_parent.lock();
    if (l_parent)
    {
        const std::shared_ptr<TransformComponent> l_parentTransform = l_parent->Transform();
        if (l_parentTransform)
        {
            l_parentTransform->UpdateGlobalTransform();
            m_globalMatrix = l_parentTransform->GetGlobalMatrix() * m_localMatrix;
        }
        else
            m_globalMatrix = m_localMatrix;
    }
    else
        m_globalMatrix = m_localMatrix;

    DecomposeMatrix(m_globalMatrix);
    m_requiresUpdate = false;

    for (std::shared_ptr<TransformComponent>& l_child : m_children)
        if (l_child)
            l_child->UpdateGlobalTransform();
}


void TransformComponent::SetLocalPosition(const Vector3& a_newPos)
{
    if (m_localPosition == a_newPos)
        return;

    m_localPosition = a_newPos;
    MarkDirty();
}

void TransformComponent::SetLocalScale(const Vector3& a_newScale)
{
    if (m_localScale == a_newScale)
        return;

    m_localScale = a_newScale;
    MarkDirty();
}


void TransformComponent::SetLocalRotationVec(const Vector3& a_newRotVec)
{
    if (m_localRotationVec == a_newRotVec)
        return;

    m_localRotationVec = a_newRotVec;
    m_localRotationQuat = Quaternion::FromEulerAngles(a_newRotVec);
    MarkDirty();
}


void TransformComponent::SetLocalRotationQuat(const Quaternion& a_newRotQuat)
{
    if (m_localRotationQuat == a_newRotQuat)
        return;

    m_localRotationQuat = a_newRotQuat;
    m_localRotationVec = a_newRotQuat.ToEulerAngles(true);
    MarkDirty();
}


void TransformComponent::SetGlobalPosition(const Vector3& a_newPos)
{
    if (GetGlobalPosition() == a_newPos)
        return;

    const std::shared_ptr<Entity> l_parent = m_parent.lock();
    if (l_parent)
    {
        const std::shared_ptr<TransformComponent> l_parentTransform = l_parent->Transform();
        if (l_parentTransform)
        {
            const Matrix4 l_invParentMatrix = l_parentTransform->GetGlobalMatrix().Inverse();
            const Matrix4 l_newLocalMatrix = Matrix4::TRS(a_newPos, m_globalRotationQuat, m_globalScale);
            m_localMatrix = l_invParentMatrix * l_newLocalMatrix;
            m_localPosition = m_localMatrix.GetTranslation();
            m_localRotationQuat = Quaternion::FromMatrix(m_localMatrix);
            m_localRotationVec = m_localRotationQuat.ToEulerAngles(true);
            m_localScale = m_localMatrix.GetScale();
            MarkDirty();
            return;
        }
    }

    SetLocalPosition(a_newPos);
}


void TransformComponent::SetGlobalScale(const Vector3& a_newScale)
{
    if (GetGlobalScale() == a_newScale)
        return;

    SetGlobalMatrix(Matrix4::TRS(m_globalPosition, m_globalRotationQuat, a_newScale));
}


void TransformComponent::SetGlobalRotationVec(const Vector3& a_newRotVec)
{
    SetGlobalRotationQuat(Quaternion::FromEulerAngles(a_newRotVec));
}


void TransformComponent::SetGlobalRotationQuat(const Quaternion& a_newRotQuat)
{
    if (m_globalRotationQuat == a_newRotQuat)
        return;

    SetGlobalMatrix(Matrix4::TRS(m_globalPosition, a_newRotQuat, m_globalScale));
}


void TransformComponent::SetGlobalMatrix(const Matrix4& a_newMatrix)
{
    m_globalMatrix = a_newMatrix;
    DecomposeMatrix(m_globalMatrix);

    const std::shared_ptr<Entity> l_parent = m_parent.lock();
    if (l_parent)
    {
        const std::shared_ptr<TransformComponent> l_parentTransform = l_parent->Transform();
        if (l_parentTransform)
            m_localMatrix = l_parentTransform->GetGlobalMatrix().Inverse() * m_globalMatrix;
    }
    else
        m_localMatrix = m_globalMatrix;

    m_localPosition = m_localMatrix.GetTranslation();
    m_localRotationQuat = Quaternion::FromMatrix(m_localMatrix);
    m_localRotationVec = m_localRotationQuat.ToEulerAngles(true);
    m_localScale = m_localMatrix.GetScale();

    MarkDirty();
}


void TransformComponent::AddChild(const std::shared_ptr<TransformComponent>& a_child)
{
    if (a_child)
        a_child->SetParent(GetOwner());
}


void TransformComponent::RemoveChild(const std::shared_ptr<TransformComponent>& a_child)
{
    std::erase(m_children, a_child);
}


void TransformComponent::SetParent(const std::shared_ptr<Entity>& a_newParent)
{
    if (m_parent.lock() == a_newParent)
        return;

    const Matrix4 l_globalMatrixBefore = GetLocalMatrix();

    if (const std::shared_ptr<Entity> l_oldParent = m_parent.lock())
        {
        if (const std::shared_ptr<TransformComponent> l_oldTransform = l_oldParent->Transform())
            std::erase_if(l_oldTransform->m_children, [this](const std::shared_ptr<TransformComponent>& c) { return c.get() == this; });
        }

    m_parent = a_newParent;

    const std::shared_ptr<TransformComponent> l_newParentTransform = a_newParent ? a_newParent->Transform() : nullptr;

    if (l_newParentTransform)
        {
        l_newParentTransform->m_children.push_back(GetOwner()->Transform());
        const Matrix4 l_newParentGlobalInverse = l_newParentTransform->GetGlobalMatrix().Inverse();
        m_localMatrix = l_newParentGlobalInverse * l_globalMatrixBefore;
    }
    else
        m_localMatrix = l_globalMatrixBefore;

    m_localPosition     = m_localMatrix.GetTranslation();
    m_localRotationQuat = Quaternion::FromMatrix(m_localMatrix);
    m_localRotationVec  = m_localRotationQuat.ToEulerAngles(true);
    m_localScale        = m_localMatrix.GetScale();

    m_requiresUpdate = true;
}


void TransformComponent::SetInterpolatedRotation(const Quaternion& a_start, const Quaternion& a_end, const float a_factor)
{
    m_localRotationQuat = Quaternion::Slerp(a_start, a_end, a_factor);
    m_localRotationVec = m_localRotationQuat.ToEulerAngles(true);
    MarkDirty();
}