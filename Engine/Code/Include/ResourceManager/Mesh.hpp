#pragma once

#include <vector>

#include "ResourceManager/Resource.hpp"
#include "Resources/ModelLoading/AssimpVertex.hpp"

class IResourceManager;

class Mesh : public IResource
{
public:
	Mesh() = default;
	~Mesh() = default;

	bool Initialize(IResourceManager* a_manager, std::string a_file) override;
	void Destroy() override;

	bool isLoaded = false;

	std::vector<AssimpVertex> m_vertices;
	std::vector<unsigned int> m_indices;

	void DebugVertices() const;

};