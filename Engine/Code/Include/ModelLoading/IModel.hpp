
#pragma once
#include "IVertex.hpp"
#include <vector>

class IModel
{
public:
	IModel() = default;
	~IModel() = default;

	void DebugVertices();
	void DebugIndices();
	
	std::vector<IVertex> m_vertices;
	std::vector<unsigned int> m_indices;
};
