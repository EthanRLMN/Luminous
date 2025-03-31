#pragma once

#include "Logger.hpp"

#include "ResourceManager.hpp"


template<typename T>
T* IResourceManager::LoadResource(const std::string& a_file)
{
	if (m_resources[a_file] == nullptr)
	{
		std::string l_info = "Trying to load " + a_file + "...";
		DEBUG_LOG_INFO("{}", l_info);

		T* l_resource = new T();
		if (l_resource && l_resource->Initialize(this, a_file))
		{
			l_info = "Initialized " + a_file + " file.";
			DEBUG_LOG_INFO("{}", l_info);
			m_resources[a_file] = l_resource;
			return l_resource;
		}

		l_info = "Failed to Initialize " + a_file + " file.";
		DEBUG_LOG_ERROR("{}", l_info);
		delete(l_resource);
		return nullptr;
	}
	std::string l_info = "Trying to get " + a_file + " since it already exists...";

	DEBUG_LOG_INFO("{}", l_info);
	return GetResource<T>(a_file);
}


template<typename T>
T* IResourceManager::GetResource(const std::string& a_file)
{
	if (m_resources[a_file] == nullptr)
	{
		std::string l_info = a_file + " cannot be found.";
		DEBUG_LOG_WARNING("{}", l_info);
	} else
	{
		if (typeid(*m_resources[a_file]) == typeid(T))
		{
			std::string l_info = a_file + " has been found.";
			DEBUG_LOG_INFO("{}", l_info);
			return dynamic_cast<T*>(m_resources[a_file]);
		}
		std::string l_info = a_file + " can be found but type provided is incorrect.";
		DEBUG_LOG_WARNING("{}", l_info);
		return nullptr;
	}
	return nullptr;
}


template<typename T>
void IResourceManager::DeleteResource(const std::string& a_file)
{
	if (m_resources[a_file] == nullptr)
	{
		std::string l_info = "Trying to delete " + a_file + " but it doesn't exist.";
		DEBUG_LOG_ERROR("{}", l_info);
	} else
	{
		if (typeid(*m_resources[a_file]) == typeid(T))
		{
			m_resources[a_file]->Destroy();
			m_resources.erase(a_file);
			if (m_resources[a_file] == nullptr)
			{
				std::string l_info = "Successfully deleted " + a_file + ".";
				DEBUG_LOG_INFO("{}", l_info);
			}
		} else
		{
			std::string l_info = a_file + " can be found but type provided is incorrect.";
			DEBUG_LOG_WARNING("{}", l_info);
		}
	}
}

