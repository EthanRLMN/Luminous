#pragma once

#include "ComponentSystem.hpp"
#include "Matrix4.hpp"

class TransformSystem final : public ComponentSystem
{
public:
    ~TransformSystem() = default;

    Maths::Matrix4 Translation = Maths::Matrix4::zero;
    Maths::Matrix4 Rotation = Maths::Matrix4::zero;
    Maths::Matrix4 Scaling = Maths::Matrix4::identity;
    //Maths::Matrix4 TRS = Maths::Matrix4::TRS(Translation, Rotation, Scaling);

    TransformSystem(const Maths::Matrix4& a_translation, const Maths::Matrix4& a_rotation,
              const Maths::Matrix4& a_scaling) : Translation(a_translation), Rotation(a_rotation), Scaling(a_scaling) {};
};
