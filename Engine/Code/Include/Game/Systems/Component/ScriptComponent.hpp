#pragma once

#include "EntityComponent.hpp"


class ScriptComponent : public EntityComponent
{
public:
    ~ScriptComponent() override = default;
    void Initialize() override {};
    void GameplayStarted() override {};
    void Update() override {};

    void SetScript(const std::string& a_path);
};
