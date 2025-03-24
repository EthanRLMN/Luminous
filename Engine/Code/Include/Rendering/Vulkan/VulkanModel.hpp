#pragma once

#include "IModel.hpp"
#include "tiny_obj_loader.h"
#include "Struct/VulkanUtilities.hpp"

class VulkanModel final : public IModel
{
public:
	void Create() override;
	void Destroy() override;

	[[nodiscard]] std::vector<Vertex> GetVertices() const { return m_vertices; }
	[[nodiscard]] std::vector<uint32_t> GetIndices() const { return m_indices; }

	VulkanModel* CastVulkan() override
	{
		return this;
	}

	const std::string MODEL_PATH{"Engine/Assets/Models/metalSonic.obj"};

private:
	std::vector<Vertex> m_vertices;
	std::vector<uint32_t> m_indices;
};
