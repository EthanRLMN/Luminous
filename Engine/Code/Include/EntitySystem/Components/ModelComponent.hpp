#pragma once


#include "ITexture.hpp"
#include "IMesh.hpp"
#include "EntitySystem/EntityComponent.hpp"



class ModelComponent : public EntityComponent
{
public:
    ~ModelComponent() = default;
    void Initialize() override ;
    void GameplayStarted() override {};
    void Update() override {};

    void SetMesh(std::string a_path);
    void SetTexture(std::string a_path);


private:
    IMesh* m_mesh;
    ITexture* m_texture;
};
