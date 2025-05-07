#pragma once


#include "ITexture.hpp"
#include "IMesh.hpp"
#include "EntitySystem/EntityComponent.hpp"



class ModelComponent : public EntityComponent
{
public:
    ~ModelComponent() = default;
    void Initialize() override {};
    void GameplayStarted() override {};
    void Update() override {};


private:
    IMesh* m_mesh;
    ITexture* m_texture;
};
