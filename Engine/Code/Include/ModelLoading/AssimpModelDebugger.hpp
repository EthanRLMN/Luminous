#pragma once

#include <vector>

#include "AssimpVertex.hpp"

class AssimpModelDebugger
{
public:
	AssimpModelDebugger() = default;
	~AssimpModelDebugger() = default;

	void DebugVertices() const;
	void DebugIndices();

	std::vector<AssimpVertex> m_vertices;
	std::vector<unsigned int> m_indices;
};
