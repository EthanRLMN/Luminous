#pragma once
#include "EntitySystem/EntityComponent.hpp"
#include <string.h>

class ModelComponent 
{
public:
    void SetModelPath(const std::string& path) { m_modelPath = path; }
    const std::string& GetModelPath() const { return m_modelPath; }
private:
    std::string m_modelPath;
};
