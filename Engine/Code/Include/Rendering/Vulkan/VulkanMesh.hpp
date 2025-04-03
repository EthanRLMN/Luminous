#pragma once

#include "IMesh.hpp"
#include "tiny_obj_loader.h"
#include "Struct/VulkanUtilities.hpp"


class VulkanMesh final : public IMesh
{
public:
    bool Create(IResourceManager* a_manager, std::string a_file,...) override;
	void Destroy() override;

	

	VulkanMesh* CastVulkan() override { return this; }

	const std::string MODEL_PATH { "Engine/Assets/Models/metalSonic.obj" };


private:
	
};
