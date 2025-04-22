#pragma once
#include "EntityComponent.hpp"
#include <string.h>

class ModelComponent : public EntityComponent
{
public:
    std::string model_Path;
    std::string texture_Path;

private:

};
