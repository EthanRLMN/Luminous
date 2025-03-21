
#pragma once
#include "IVertex.hpp"
#include <vector>

class IModel
{
public:
	IModel() = default;
	~IModel() = default;

	//virtual void Initialize() = 0;

private:
	std::vector<IVertex> m_vertices;
	std::vector<unsigned int> m_indices;
};
