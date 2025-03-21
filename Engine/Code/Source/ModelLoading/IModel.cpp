#include "ModelLoading/IModel.hpp"
#include "Logger.hpp"
#include <iostream>


void IModel::DebugVertices()
{
	for (int i = 0; i < m_vertices.size(); ++i)
	{
		std::string l_pos = std::to_string(m_vertices[i].m_position.x) + ", "
			+ std::to_string(m_vertices[i].m_position.y) + ", " 
			+ std::to_string(m_vertices[i].m_position.z);
		DEBUG_LOG_INFO("{}", l_pos);
	}

	for (int i = 0; i < m_vertices.size(); ++i)
	{
		std::string l_normal = std::to_string(m_vertices[i].m_normal.x) + ", "
			+ std::to_string(m_vertices[i].m_normal.y) + ", "
			+ std::to_string(m_vertices[i].m_normal.z);
		DEBUG_LOG_INFO("{}", l_normal);
	}

	for (int i = 0; i < m_vertices.size(); ++i)
	{
		std::string l_texCoords = std::to_string(m_vertices[i].m_texcoord.x) + ", "
			+ std::to_string(m_vertices[i].m_texcoord.y);
		DEBUG_LOG_INFO("{}", l_texCoords);
	}

}

void IModel::DebugIndices()
{
	for (int i = 0; i < m_indices.size(); ++i)
	{
		DEBUG_LOG_INFO("{}", m_indices[i]);
	}
}