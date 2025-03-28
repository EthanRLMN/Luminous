#pragma once
#include "ModelLoading/AssimpVertex.hpp"

#include "ResourceManager/Resource.hpp"
#include <vector>

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