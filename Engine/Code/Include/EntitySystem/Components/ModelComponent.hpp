#pragma once

#include <string>

#include "EntitySystem/EntityComponent.hpp"


class ModelComponent : public EntityComponent
{
public:
    ModelComponent() = default;
    ~ModelComponent() override = default;

    void Create() override {};
    void Destroy() override {};
    void Update() override {};

    std::string m_modelPath;
    std::string m_texturePath;

};
