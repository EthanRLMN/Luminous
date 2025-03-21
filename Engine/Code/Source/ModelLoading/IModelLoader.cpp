#include "ModelLoading/IModelLoader.hpp"
#include <string>


IModel IModelLoader::LoadModel(const char* a_file)
{
	
	Assimp::Importer l_importer;
	char l_buffer[1024];
	if (_getcwd(l_buffer, 1024) != NULL) {
		std::cout << "Current working directory: " << l_buffer << '\n';
	}
	DebugExtensionsList(&l_importer);

	const aiScene* scene = l_importer.ReadFile(a_file,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::string l_info = "ASSIMP : " + std::string(l_importer.GetErrorString());
		DEBUG_LOG_ERROR("{}", l_info);
		return IModel();
	}else
	{
		IModel l_model;
		aiMesh* mesh = scene->mMeshes[0];
		std::string l_info = std::string(a_file) + " file has been red by the parser.";
		DEBUG_LOG_INFO("{}", l_info);
		
		if (mesh)
		{
			for (unsigned int i = 0; i < mesh->mNumVertices; i++) //SetupVertices
			{
				IVertex l_currentVertex;
				Maths::Vector3 l_vertPosition;

				l_vertPosition.x = mesh->mVertices[i].x;
				l_vertPosition.y = mesh->mVertices[i].y;
				l_vertPosition.z = mesh->mVertices[i].z;

				std::string l_pos = std::to_string(mesh->mVertices[i].x) + ", "
					+ std::to_string(mesh->mVertices[i].y) + ", "
					+ std::to_string(mesh->mVertices[i].z);
				DEBUG_LOG_INFO("{}", l_pos);

				l_currentVertex.m_position = l_vertPosition;

				Maths::Vector2 l_vertTexCoords;
				if (mesh->mTextureCoords[0])
				{
					l_vertTexCoords.x = mesh->mTextureCoords[0][i].x;
					l_vertTexCoords.y = mesh->mTextureCoords[0][i].y;
				}
				else
				{
					l_vertTexCoords.x = 0;
					l_vertTexCoords.y = 0;
				}
				l_currentVertex.m_texcoord = l_vertTexCoords;

				Maths::Vector3 l_vertNormals;
				l_vertNormals.x = mesh->mNormals[i].x;
				l_vertNormals.y = mesh->mNormals[i].y;
				l_vertNormals.z = mesh->mNormals[i].z;

				l_currentVertex.m_normal = l_vertNormals;

				l_model.m_vertices.push_back(l_currentVertex);

			}

			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				for (unsigned int j = 0; j < face.mNumIndices; j++)
					l_model.m_indices.push_back(face.mIndices[j]);
			}

			return l_model;

		}else
		{
			return l_model;
		}

	}


}

void IModelLoader::DebugExtensionsList(Assimp::Importer* a_importer)
{
	std::string l_extensions;
	a_importer->GetExtensionList(l_extensions);
	std::string l_info = "Assimp currently supports : " + l_extensions;
	DEBUG_LOG_INFO("{}", l_info);
}
