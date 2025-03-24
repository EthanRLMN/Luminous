#pragma once

#include <unordered_map>
#include "Resource.hpp"

class ResourceManager
{
public:
	ResourceManager() = default;
	~ResourceManager() = default;

	std::unordered_map<std::string, Resource*> m_resources;

	template <typename T>
	const T* LoadResource(std::string a_file);
	const T* GetResource(std::string a_file);
	const T* DeleteResource(std::string a_file)


};
