#pragma once
#include <string>

class Resource
{
public:
	virtual void Initialize(ResourceManager* a_manager, std::string a_file) = 0;
	virtual void Destroy() = 0;
};