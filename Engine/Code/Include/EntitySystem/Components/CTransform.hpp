#pragma once
#include "EntityComponent.hpp"
#include "Vector3.hpp"
#include "Quaternion.hpp"

class CTransform : public EntityComponent
{
public:
    Maths::Vector3 position = Maths::Vector3::Zero;
    Maths::Quaternion rotation = Maths::Quaternion::Identity();
    Maths::Vector3 scale = Maths::Vector3::One;
private:

}
