#include "Resources/ModelLoading/AssimpModelDebugger.hpp"

#include "Logger.hpp"

void AssimpModelDebugger::DebugVertices() const
{
	for (const AssimpVertex& l_vertice : m_vertices)
	{
		std::string l_pos = std::to_string(l_vertice.m_position.x) + ", "
		                    + std::to_string(l_vertice.m_position.y) + ", "
		                    + std::to_string(l_vertice.m_position.z);
		DEBUG_LOG_INFO("{}", l_pos);
	}

	for (const AssimpVertex& l_vertice : m_vertices)
	{
		std::string l_normal = std::to_string(l_vertice.m_normal.x) + ", "
		                       + std::to_string(l_vertice.m_normal.y) + ", "
		                       + std::to_string(l_vertice.m_normal.z);
		DEBUG_LOG_INFO("{}", l_normal);
	}

	for (const AssimpVertex& l_vertice : m_vertices)
	{
		std::string l_texCoords = std::to_string(l_vertice.m_texCoords.x) + ", "
		                          + std::to_string(l_vertice.m_texCoords.y);
		DEBUG_LOG_INFO("{}", l_texCoords);
	}
}

void AssimpModelDebugger::DebugIndices()
{
	for (unsigned int& l_indice : m_indices)
		DEBUG_LOG_INFO("{}", l_indice);
}
