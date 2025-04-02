#pragma once

#include "Logger.hpp"
#include "ResourceManager/Resource.hpp"

class VulkanMesh;

class IMesh : public IResource
{
public:
    IMesh() = default;
	~IMesh() = default;
    bool Create(IResourceManager* a_manager, std::string a_file) override { return false; };
    void Destroy() override { return; };

	virtual VulkanMesh* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan Model : Cast is Wrong!\n");
		return nullptr;
	}
};