#include <unordered_map>

#define TINYOBJLOADER_IMPLEMENTATION
#include "Rendering/Vulkan/VulkanModel.hpp"

void VulkanModel::Create()
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	if (!LoadObj(&attrib, &shapes, &materials, &warn, &err, MODEL_PATH.c_str()))
	{
		DEBUG_LOG_ERROR("{}{}", warn, err);
		return;
	}

	std::unordered_map<Vertex, uint32_t, VertexHasher> uniqueVertices{};

	for (const auto& shape: shapes)
	{
		for (const auto& index: shape.mesh.indices)
		{
			Vertex vertex;
			vertex.pos = {
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
			};

			vertex.texCoord = {
				attrib.texcoords[2 * index.texcoord_index + 0],
				1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
			};

			vertex.color = {1.0f, 1.0f, 1.0f};

			if (!uniqueVertices.contains(vertex))
			{
				uniqueVertices[vertex] = static_cast<uint32_t>(m_vertices.size());
				m_vertices.push_back(vertex);
			}

			m_indices.push_back(uniqueVertices[vertex]);
		}
	}
}


void VulkanModel::Destroy()
{
}
