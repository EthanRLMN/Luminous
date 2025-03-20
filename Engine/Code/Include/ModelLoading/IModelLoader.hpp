



#include <iostream>

#include <direct.h>
#include "Utils/Exporter.hpp"
#include "GLFW/../../../Libs/assimp/include/assimp/Importer.hpp"
#include "GLFW/../../../Libs/assimp/include/assimp/scene.h"
#include "GLFW/../../../Libs/assimp/include/assimp/postprocess.h"
#include "GLFW/../../../Libs/assimp/include/assimp/BaseImporter.h"

class LUMINOUS_ENGINE_API IModelLoader
{
public:
	IModelLoader() = default;
	~IModelLoader() = default;

	void LoadModel(const char* a_file);
};