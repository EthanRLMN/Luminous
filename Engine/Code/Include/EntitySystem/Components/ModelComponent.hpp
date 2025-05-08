#pragma once


#include "IMesh.hpp"
#include "ITexture.hpp"
#include "EntitySystem/EntityComponent.hpp"


class ModelComponent : public EntityComponent
{
public:
    ~ModelComponent() override = default;
    void Initialize() override { };
    void GameplayStarted() override {};
    void Update() override {};


private:
    //IMesh* m_mesh { nullptr };
    //ITexture* m_texture { nullptr };
};
