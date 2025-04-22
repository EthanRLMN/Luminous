#pragma once
#include "BaseComponent.hpp"


#include "Vector3.hpp"
#include "Quaternion.hpp"

class TransformEntity : public BaseComponent
{
public:
    Maths::Vector3 position = Maths::Vector3::Zero;
    Maths::Quaternion rotation = Maths::Quaternion::Identity();
    Maths::Vector3 scale = Maths::Vector3::One;
private:

}
