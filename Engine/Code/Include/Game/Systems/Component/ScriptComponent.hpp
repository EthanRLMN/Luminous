#pragma once

#include "EntityComponent.hpp"

#include "Game/Systems/Scripts/BaseScript.hpp"


class ScriptComponent : public EntityComponent
{
public:
    ~ScriptComponent() override = default;
    void Initialize() override {};
    void GameplayStarted() override 
    {
        if (m_script != nullptr)
            m_script->Init();
    };
    void Update() override 
    {
        if (m_script != nullptr)
            m_script->Update();
    };

    void SetScript(BaseScript* a_script)
    {
        m_script = a_script;
        m_script->m_owner = GetOwner();
    }

    BaseScript* m_script;

};
