#include "ModelLoading/IModelLoader.hpp"

void IModelLoader::LoadModel(const char* a_file)
{
	Assimp::Importer importer;
	char buffer[1024];
	if (_getcwd(buffer, 1024) != NULL) {
		// print the current working directory
		std::cout << "Current working directory: " << buffer << '\n';
	}
	const aiScene* scene = importer.ReadFile("/Assets/Models/sphere.obj", aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

	if (scene != nullptr)
	{
		aiMesh* mesh = scene->mMeshes[0];
		std::cout << "gentil visual studio\n";
	}else 
	{
		std::cout << "paload\n";
	}

}
