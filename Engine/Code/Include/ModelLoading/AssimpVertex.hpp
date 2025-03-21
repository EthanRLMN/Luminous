#pragma once

#include "Vector2.hpp"
#include "Vector3.hpp"

struct AssimpVertex
{
	Maths::Vector3 m_position = Maths::Vector3::Zero;
	Maths::Vector2 m_texCoords = Maths::Vector2::One;
	Maths::Vector3 m_normal = Maths::Vector3::Zero;
};
