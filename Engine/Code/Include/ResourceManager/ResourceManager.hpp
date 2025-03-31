#pragma once

#include <unordered_map>
#include "Resource.hpp"
#include "Logger.hpp"
#include "ModelLoading/AssimpModelLoader.hpp"

class IResourceManager
{
public:
	IResourceManager();
	~IResourceManager();

	std::unordered_map<std::string, IResource*> m_resources;

	template<typename T> T* LoadResource(std::string a_file);
	template<typename T> T* GetResource(std::string a_file);
	template<typename T> void DeleteResource(std::string a_file);

	AssimpModelLoader* GetMeshLoader() { return m_meshLoader; };

private:
	AssimpModelLoader* m_meshLoader;
	int mecouy = 1;

};

#include "ResourceManager/ResourceManager.inl"
