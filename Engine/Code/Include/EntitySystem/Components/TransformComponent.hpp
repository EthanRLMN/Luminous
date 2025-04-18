#pragma once
#include "BaseComponent.hpp"


#include "Vector3.hpp"

class TransformEntity : public BaseComponent
{
public:
    Maths::Vector3 position = Maths::Vector3::Zero;
    Maths::Vector3 rotation = Maths::Vector3::Zero;
    Maths::Vector3 scale = Maths::Vector3::One;
private:

}
