#pragma once
#include "Vector3.hpp"
#include "Vector2.hpp"

struct IVertex
{
	Maths::Vector3 m_position;
	Maths::Vector2 m_texcoord;
	Maths::Vector3 m_normal;
};