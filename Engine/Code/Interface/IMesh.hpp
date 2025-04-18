#pragma once

#include "Logger.hpp"
#include "ResourceManager/Resource.hpp"
#include "Struct/VulkanUtilities.hpp"

class VulkanMesh;

class IMesh : public IResource
{
public:
    IMesh() = default;
    bool Create(IResourceManager* a_manager, const IResourceParams& a_params) override { return false; };

	virtual VulkanMesh* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan Model : Cast is Wrong!\n");
		return nullptr;
	}

	[[nodiscard]] std::vector<Vertex> GetVertices() const { return m_vertices; }
    [[nodiscard]] std::vector<uint32_t> GetIndices() const { return m_indices; }

	std::vector<Vertex> m_vertices;
    std::vector<uint32_t> m_indices;

};