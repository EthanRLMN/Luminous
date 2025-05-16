#pragma once

#include <memory>

#include "EntityComponent.hpp"


class Entity;

class MeshRendererComponent : public EntityComponent
{
public:
    ~MeshRendererComponent() override = default;
    void Initialize() override {};
    void GameplayStarted() override {};
    void Update() override {};

    /*          Getters         */
    [[nodiscard]] inline bool GetActive() const { return m_isActive; }
    [[nodiscard]] inline std::shared_ptr<Entity> GetOwner() const override { return p_owner; }

    /*          Setters         */
    inline void SetActive(const bool a_active) { m_isActive = a_active; }
    inline void SetOwner(const std::shared_ptr<Entity>& a_relatedEntity) override { p_owner = a_relatedEntity; }


private:
    bool m_isActive { false };
};
