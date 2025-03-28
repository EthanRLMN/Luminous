#include "ResourceManager/ResourceManager.hpp"


template<typename T> T* IResourceManager::LoadResource(std::string a_file)
{
	if (m_resources[a_file] == nullptr)
	{
		std::string l_info = "Trying to load " + a_file + "...";
		DEBUG_LOG_INFO("{}", l_info);

		T* l_resource = new T();
		if (l_resource && l_resource->Initialize(this, a_file))
		{
			std::string l_info = "Initialized " + a_file + " file.";
			DEBUG_LOG_INFO("{}", l_info);
			m_resources[a_file] = l_resource;
			return l_resource;
		}
		else
		{
			std::string l_info = "Failed to Initialize " + a_file + " file.";
			DEBUG_LOG_ERROR("{}", l_info);
			delete(l_resource);
			return nullptr;
		}
	}
	else
	{
		std::string l_info = "Trying to replace " + a_file + " since it already exists...";
		DEBUG_LOG_INFO("{}", l_info);
	}
	return nullptr;
}

template<typename T> T* IResourceManager::GetResource(std::string a_file)
{
	if (m_resources[a_file] == nullptr)
	{
		std::string l_info = a_file + " cannot be found.";
		DEBUG_LOG_WARNING("{}", l_info);
	}
	else
	{
		
	}
	return nullptr;
}


template<typename T> void IResourceManager::DeleteResource(std::string a_file)
{

}

