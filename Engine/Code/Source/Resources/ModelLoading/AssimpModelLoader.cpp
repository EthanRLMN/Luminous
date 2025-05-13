#include <direct.h>
#include <string>

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#include "Logger.hpp"

#include "Resources/ModelLoading/AssimpModelLoader.hpp"


void AssimpModelLoader::LoadModel(IMesh* a_mesh, const char* a_file)
{
    Assimp::Importer l_importer{};
    std::array<char, 1024> l_buffer{};
    if (getcwd(l_buffer.data(), 1024) != nullptr)
        DEBUG_LOG_INFO("Current working directory: {}\n", l_buffer.data());

    DebugExtensionsList(&l_importer);
    const aiScene* l_scene = l_importer.ReadFile(a_file, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_ImproveCacheLocality | aiProcess_RemoveRedundantMaterials | aiProcess_FindDegenerates | aiProcess_FindInvalidData | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph | aiProcess_GenSmoothNormals | aiProcess_FixInfacingNormals);
    if (!l_scene || l_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !l_scene->mRootNode)
    {
        std::string l_info = "ASSIMP : " + std::string(l_importer.GetErrorString());
        DEBUG_LOG_ERROR("{}", l_info);
        return;
    }

    if (l_scene->mNumMeshes == 0)
    {
        DEBUG_LOG_ERROR("Could not load any mesh from the file: {}", a_file);
        return;
    }

    const aiMesh* l_mesh = l_scene->mMeshes[0];
    std::string l_info = std::string(a_file) + " file has been read by the parser.";
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
        Vertex l_currentVertex{};

        l_currentVertex.pos = {
            a_mesh->mVertices[i].x,
            a_mesh->mVertices[i].y,
            a_mesh->mVertices[i].z
        };

        if (a_mesh->mTextureCoords[0])
        {
            l_currentVertex.texCoord = {
                a_mesh->mTextureCoords[0][i].x,
                1.0f - a_mesh->mTextureCoords[0][i].y
            };
        }
        else
            l_currentVertex.texCoord = { 0.0f, 0.0f };


        if (a_mesh->HasNormals())
        {
            l_currentVertex.normal = {
                a_mesh->mNormals[i].x,
                a_mesh->mNormals[i].y,
                a_mesh->mNormals[i].z
            };
        }
        else
            l_currentVertex.normal = { 0.0f, 0.0f, 0.0f };


        if (a_mesh->HasVertexColors(0))
        {
            const aiColor4D& c = a_mesh->mColors[0][i];
            l_currentVertex.color = { c.r, c.g, c.b };
        }

        l_vertices.push_back(l_currentVertex);
    }
    return l_vertices;
}


std::vector<unsigned int> AssimpModelLoader::SetupIndices(const aiMesh* a_mesh)
{
    std::vector<unsigned int> l_indices{};
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
    std::string l_extensions{};
    a_importer->GetExtensionList(l_extensions);
    std::string l_info = "Assimp currently supports : " + l_extensions;
    DEBUG_LOG_INFO("{}", l_info);
}
