#include "Game/Systems/Physics/RigidBody.hpp"
#include "Vector3.hpp"
#include "Quaternion.hpp"

#include "Game/Systems/Entity/Entity.hpp"
#include "Game/Systems/Component/RigidbodyComponent.hpp"

void RigidBody::UpdateToTransform() 
{
    JPH::Vec3 l_bodyPosition = GetPosition();
    JPH::Quat l_bodyRotation = GetRotation();
    Maths::Vector3 l_position = Maths::Vector3(l_bodyPosition.GetX(), l_bodyPosition.GetY(), l_bodyPosition.GetZ());
    Maths::Quaternion l_rotation = Maths::Quaternion(-l_bodyRotation.GetX(), -l_bodyRotation.GetY(), -l_bodyRotation.GetZ(), l_bodyRotation.GetW());
    GetParentComponent()->GetEntity().get()->Transform()->SetLocalPosition(l_position);
    GetParentComponent()->GetEntity().get()->Transform()->SetLocalRotationQuat(l_rotation);


}
