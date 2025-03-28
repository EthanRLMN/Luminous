#include "ResourceManager/ResourceManager.hpp"


IResourceManager::IResourceManager()
{
	m_meshLoader = new AssimpModelLoader;
}

IResourceManager::~IResourceManager()
{
	delete(m_meshLoader);
}


IResource* IResourceManager::GetResource(std::string a_file)
{
	return nullptr;
}

