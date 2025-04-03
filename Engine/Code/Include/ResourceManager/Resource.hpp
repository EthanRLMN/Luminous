#pragma once
#include <string>
#include <cstdarg>

class IResourceManager;

class IResource
{
public:

	IResource() = default;
	~IResource() = default;

	virtual bool Create(IResourceManager* a_manager, std::string a_file,...) = 0;
	virtual void Destroy() = 0;
    bool isLoaded = false;


};