#pragma once
#include "Logger.hpp"

#include "ResourceManager.hpp"
#include "Rendering/Vulkan/VulkanShader.hpp"
#include "Rendering/Vulkan/VulkanTexture.hpp"
#include "Rendering/Vulkan/VulkanMesh.hpp"

class VulkanTexture;
class VulkanMesh;
class VulkanShader;

template<typename T>
T* ResourceManager::LoadResource(const IResourceParams a_params)
{
    std::string l_file = "";

	if (typeid(T) == typeid(VulkanTexture))
        l_file = a_params.m_texturePath;
    else if (typeid(T) == typeid(VulkanMesh))
        l_file = a_params.m_meshPath;
    else if (typeid(T) == typeid(VulkanShader))
    {
        std::string l_path = "v=" + a_params.m_vertexShaderPath + ", f=" + a_params.m_fragmentShaderPath + ", t=" + a_params.m_tesselationShaderPath + ", g=" + a_params.m_geometryShaderPath;
        l_file = l_path;
        DEBUG_LOG_INFO("{}", l_file);
    }

	if (m_resources[l_file] == nullptr)
	{
        std::string l_info = "Trying to load " + l_file + "...";
		DEBUG_LOG_INFO("{}", l_info);

		T* l_resource = new T();
		if (l_resource && l_resource->Create(a_params))
		{
            l_info = "Initialized " + l_file + " file.";
			DEBUG_LOG_INFO("{}", l_info);
            m_resources[l_file] = l_resource;
			return l_resource;
		}

		l_info = "Failed to Initialize " + l_file + " file.";
		DEBUG_LOG_ERROR("{}", l_info);
		delete(l_resource);
		return nullptr;
	}
    std::string l_info = "Trying to get " + l_file + " since it already exists...";

	DEBUG_LOG_INFO("{}", l_info);
    return GetResource<T>(l_file);
}


template<typename T>
T* ResourceManager::GetResource(const std::string& a_file)
{
    const auto l_it = m_resources.find(a_file);
    if (l_it == m_resources.end() || l_it->second == nullptr)
    {
        std::string l_info = a_file + " cannot be found.";
        DEBUG_LOG_WARNING("{}", l_info);
        return nullptr;
    }

    T* l_casted = dynamic_cast<T*>(l_it->second);
    if (l_casted != nullptr)
    {
        std::string l_info = a_file + " has been found.";
        DEBUG_LOG_INFO("{}", l_info);
        return l_casted;
    }

    std::string l_info = a_file + " can be found but type provided is incorrect.";
    DEBUG_LOG_WARNING("{}", l_info);
    return nullptr;
}


template<typename T>
void ResourceManager::DeleteResource(const std::string& a_file, IDevice* a_device)
{
    const auto l_it = m_resources.find(a_file);
    if (l_it == m_resources.end() || l_it->second == nullptr)
    {
        std::string l_info = "Trying to delete " + a_file + " but it doesn't exist.";
        DEBUG_LOG_ERROR("{}", l_info);
        return;
    }

    T* l_casted = dynamic_cast<T*>(l_it->second);
    if (l_casted != nullptr)
    {
        l_it->second->Destroy(a_device);
        m_resources.erase(l_it);
        std::string l_info = "Successfully deleted " + a_file + ".";
        DEBUG_LOG_INFO("{}", l_info);
    }
    else
    {
        std::string l_info = a_file + " can be found but type provided is incorrect.";
        DEBUG_LOG_WARNING("{}", l_info);
    }
}