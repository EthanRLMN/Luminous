#pragma once

#include "EntitySystem/EntityComponent.hpp"
#include "Quaternion.hpp"
#include "Vector3.hpp"
#include "Matrix4.hpp"

class TransformComponent 
{
public:
    Maths::Vector3 position = Maths::Vector3::Zero;
    Maths::Quaternion rotation = Maths::Quaternion::Identity;
    Maths::Vector3 scale = Maths::Vector3::One;

    Maths::Matrix4 TRS;
};
