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
		return;
	}else
	{
		IModel l_model;
		aiMesh* mesh = scene->mMeshes[0];
		std::string l_info = std::string(a_file) + " file has been red by the parser.";
		DEBUG_LOG_INFO("{}", l_info);
		if (mesh)
		{

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
