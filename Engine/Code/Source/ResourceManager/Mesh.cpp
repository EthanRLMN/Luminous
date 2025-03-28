#include "ResourceManager/Mesh.hpp"
#include "ResourceManager/ResourceManager.hpp"

bool Mesh::Initialize(IResourceManager* a_manager, std::string a_file)
{
	a_manager->GetMeshLoader()->LoadModel(this,a_file.c_str());
	return isLoaded;
}

void Mesh::DebugVertices() const
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

void Mesh::Destroy()
{

}