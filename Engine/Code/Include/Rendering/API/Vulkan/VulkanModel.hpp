#pragma once

#include "IModel.hpp"
#include "tiny_obj_loader.h"
#include "Struct/VulkanUtilities.hpp"

class VulkanModel final : public IModel {

public:
	void Create() override;
	void Destroy() override;

	VulkanModel* CastVulkan() override { return this; }

	const std::string MODEL_PATH{ "Engine/Assets/Models/metalSonic.obj" };
private:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
};