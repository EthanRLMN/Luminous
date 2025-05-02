#pragma once
#include "EntitySystem/EntityComponent.hpp"
#include <string.h>

class ModelComponent 
{
public:
    void SetModelPath(const std::string& path) { modelPath = path; }
    const std::string& GetModelPath() const { return modelPath; }
private:
    std::string modelPath;
};
