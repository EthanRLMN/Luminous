#pragma once
#include "EntityComponent.hpp"
#include "IMesh.hpp"
#include "ITexture.hpp"


class ModelComponent : public EntityComponent
{
public:
    ~ModelComponent() override = default;
    void Initialize() override ;
    void GameplayStarted() override {};
    void Update() override {};

    void SetMesh(const std::string& a_path);
    void SetTexture(const std::string& a_path);

    [[nodiscard]] IMesh* GetMesh() const { return m_mesh; };
    [[nodiscard]] ITexture* GetTexture() const { return m_texture; };

private:
    IMesh* m_mesh { nullptr };
    ITexture* m_texture { nullptr };
};
