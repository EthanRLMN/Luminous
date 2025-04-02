#pragma once

#include "assimp/BaseImporter.h"
#include "assimp/scene.h"

#include "ResourceManager/Mesh.hpp"
#include "IModel.hpp"

class AssimpModelLoader
{
public:
	AssimpModelLoader() = default;
	~AssimpModelLoader() = default;

	void LoadModel(IMesh* a_mesh, const char* a_file);
    std::vector<Vertex> SetupVertices(const aiMesh* a_mesh);
	std::vector<unsigned int> SetupIndices(const aiMesh* a_mesh);
	void DebugExtensionsList(const Assimp::Importer* a_importer);
};
