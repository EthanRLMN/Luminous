#include <direct.h>
#include <string>

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#include "Logger.hpp"

#include "Resources/ModelLoading/AssimpModelLoader.hpp"


void AssimpModelLoader::LoadModel(IMesh* a_mesh, const char* a_file)
{
    Assimp::Importer l_importer { };
    char l_buffer[1024];
    if (_getcwd(l_buffer, 1024) != nullptr)
        DEBUG_LOG_INFO("Current working directory: {}\n", l_buffer);

    DebugExtensionsList(&l_importer);
    const aiScene* l_scene = l_importer.ReadFile(a_file, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
    if (!l_scene || l_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !l_scene->mRootNode)
    {
        std::string l_info = "ASSIMP : " + std::string(l_importer.GetErrorString());
        DEBUG_LOG_ERROR("{}", l_info);
        return;
    }

    const aiMesh* l_mesh = l_scene->mMeshes[0];
    std::string l_info = std::string(a_file) + " file has been red by the parser.";
    DEBUG_LOG_INFO("{}", l_info);

    if (l_mesh)
    {
        a_mesh->m_vertices = SetupVertices(l_mesh);
        a_mesh->m_indices = SetupIndices(l_mesh);
        l_info = std::string(a_file) + " has been successfully parsed.";
        DEBUG_LOG_INFO("{}", l_info);
        a_mesh->SetLoaded(true);
    }
}


std::vector<Vertex> AssimpModelLoader::SetupVertices(const aiMesh* a_mesh)
{
    std::vector<Vertex> l_vertices{};
	for (unsigned int i = 0; i < a_mesh->mNumVertices; ++i)
	{
		Vertex l_currentVertex { };

		Maths::Vector3 l_vertPosition { };
		l_vertPosition.x = a_mesh->mVertices[i].x;
		l_vertPosition.y = a_mesh->mVertices[i].y;
		l_vertPosition.z = a_mesh->mVertices[i].z;
		l_currentVertex.pos = l_vertPosition;

		Maths::Vector2 l_vertTexCoords { };
		if (a_mesh->mTextureCoords[0])
		{
			l_vertTexCoords.x = a_mesh->mTextureCoords[0][i].x;
			l_vertTexCoords.y = 1.0f - a_mesh->mTextureCoords[0][i].y;
		} else
		{
			l_vertTexCoords.x = 0;
			l_vertTexCoords.y = 0;
		}
		l_currentVertex.texCoord = l_vertTexCoords;

		Maths::Vector3 l_vertNormals { };
		l_vertNormals.x = a_mesh->mNormals[i].x;
		l_vertNormals.y = a_mesh->mNormals[i].y;
		l_vertNormals.z = a_mesh->mNormals[i].z;
		l_currentVertex.color = l_vertNormals;

        l_vertices.push_back(l_currentVertex);
    }
    return l_vertices;
}


std::vector<unsigned int> AssimpModelLoader::SetupIndices(const aiMesh* a_mesh)
{
    std::vector<unsigned int> l_indices { };
    for (unsigned int i = 0; i < a_mesh->mNumFaces; ++i)
    {
        const aiFace l_face = a_mesh->mFaces[i];
        for (unsigned int j = 0; j < l_face.mNumIndices; ++j)
            l_indices.push_back(l_face.mIndices[j]);
    }
    return l_indices;
}


void AssimpModelLoader::DebugExtensionsList(const Assimp::Importer* a_importer)
{
    std::string l_extensions { };
    a_importer->GetExtensionList(l_extensions);
    std::string l_info = "Assimp currently supports : " + l_extensions;
    DEBUG_LOG_INFO("{}", l_info);
}
