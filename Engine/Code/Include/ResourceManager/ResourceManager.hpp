#pragma once

#include <unordered_map>

#include "Resource.hpp"

#include "Resources/ModelLoading/AssimpModelLoader.hpp"


class IResourceManager
{
public:
	IResourceManager();
	~IResourceManager();

	std::unordered_map<std::string, IResource*> m_resources;

	template<typename T> T* LoadResource(const std::string& a_file);
	template<typename T> T* GetResource(const std::string& a_file);
	template<typename T> void DeleteResource(const std::string& a_file);

	[[nodiscard]] AssimpModelLoader* GetMeshLoader() const { return m_meshLoader; };

private:
	AssimpModelLoader* m_meshLoader;
	int mecouy = 1;

};

#include "ResourceManager/ResourceManager.inl"
