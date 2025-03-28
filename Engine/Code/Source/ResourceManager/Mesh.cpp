#include "ResourceManager/Mesh.hpp"


bool Mesh::Initialize(IResourceManager* a_manager, std::string a_file)
{
	m_meshDebug = a_manager->GetMeshLoader()->LoadModel(a_file.c_str());
	return m_meshDebug.isLoaded;
}

void Mesh::Destroy()
{

}