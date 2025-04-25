#pragma once
#include "EntityComponent.hpp"
#include <string.h>

class CModel : public EntityComponent
{
public:
    std::string m_modelPath;
    std::string m_texturePath;

private:

};
