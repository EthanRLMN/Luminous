#pragma once

#include "assimp/BaseImporter.h"
#include "assimp/scene.h"

#include "IMesh.hpp"

class AssimpModelLoader
{
public:
	AssimpModelLoader() = default;
	~AssimpModelLoader() = default;

    static void LoadModel(IMesh* a_mesh, const char* a_file);
    static std::vector<Vertex> SetupVertices(const aiMesh* a_mesh);
    static std::vector<unsigned int> SetupIndices(const aiMesh* a_mesh);
    static void DebugExtensionsList(const Assimp::Importer* a_importer);
};
