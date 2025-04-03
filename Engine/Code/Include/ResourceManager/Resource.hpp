#pragma once

#include <string>

class IResourceManager;


class IResource
{
public:
	IResource() = default;
    virtual ~IResource() = default;

	virtual bool Initialize(const IResourceManager* a_manager, const std::string& a_file) = 0;
	virtual void Destroy() = 0;
};