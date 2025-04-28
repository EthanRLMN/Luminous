#pragma once
#include "EntityComponent.hpp"
#include <string.h>

class ModelComponent : public EntityComponent
{
public:
    std::string m_modelPath;
    std::string m_texturePath;

private:

};
