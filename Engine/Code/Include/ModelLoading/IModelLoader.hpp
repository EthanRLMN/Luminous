


#include <iostream>

#include <direct.h>
#include "Utils/Exporter.hpp"
#include "GLFW/../../../Libs/assimp/include/assimp/Importer.hpp"
#include "GLFW/../../../Libs/assimp/include/assimp/scene.h"
#include "GLFW/../../../Libs/assimp/include/assimp/postprocess.h"
#include "GLFW/../../../Libs/assimp/include/assimp/BaseImporter.h"
#include "Logger.hpp"
#include "ModelLoading/IModel.hpp"

class LUMINOUS_ENGINE_API IModelLoader
{
public:
	IModelLoader() = default;
	~IModelLoader() = default;

	IModel LoadModel(const char* a_file);
	void DebugExtensionsList(Assimp::Importer* a_importer);
};