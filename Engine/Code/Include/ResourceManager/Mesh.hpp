#pragma once

#include <vector>

#include "ResourceManager/Resource.hpp"
#include "Resources/ModelLoading/AssimpVertex.hpp"

class IResourceManager;

class Mesh : public IResource
{
public:
	Mesh() = default;
	~Mesh() override = default;

	bool Initialize(const IResourceManager* a_manager, const std::string& a_file) override;
	void Destroy() override;

	bool isLoaded = false;

	std::vector<AssimpVertex> m_vertices;
	std::vector<unsigned int> m_indices;

	void DebugVertices() const;

};