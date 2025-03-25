#pragma once

#include <unordered_map>
#include "Resource.hpp"
#include "Logger.hpp"
#include "ModelLoading/AssimpModelLoader.hpp"

class IResourceManager
{
public:
	IResourceManager() = default;
	~IResourceManager() = default;

	std::unordered_map<std::string, IResource*> m_resources;

	template<typename T> T* LoadResource(std::string a_file);
	IResource* GetResource(std::string a_file);
	IResource* DeleteResource(std::string a_file);

private:
	AssimpModelLoader m_meshLoader;

};

#include "ResourceManager/ResourceManager.inl"
