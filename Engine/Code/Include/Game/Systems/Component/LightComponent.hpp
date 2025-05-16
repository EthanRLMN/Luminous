#pragma once

#include "EntityComponent.hpp"
#include "Game/Systems/Light/Light.hpp"


class LightComponent : public EntityComponent
{
public:
    void Initialize() override {}
    void GameplayStarted() override {}
    void Update() override;


    inline std::shared_ptr<Entity> GetOwner() const override { return p_owner; };
    inline LightData& GetLight() { return m_lightData; }
    inline Maths::Vector3 GetPosition() const { return m_lightData.m_position; }
    inline Maths::Vector3 GetDirection() const { return m_lightData.m_direction; }
    inline Maths::Vector3 GetColor() const { return m_lightData.m_color; }
    inline float GetIntensity() const { return m_lightData.m_intensity; }
    inline float GetAmbientStrength() const { return m_lightData.m_ambientStrength; }
    inline float GetSpecularStrength() const { return m_lightData.m_specularStrength; }
    inline LightType GetType() const { return m_lightData.m_type; }
    inline bool IsActive() const { return m_isActive; }

    inline void SetOwner(const std::shared_ptr<Entity>& a_relatedEntity) override { p_owner = a_relatedEntity; }
    inline void SetLight(const LightData& a_lightData) { m_lightData = a_lightData; }
    inline void SetActive(const bool a_isActive) { m_isActive = a_isActive; }
    inline void SetPosition(const Maths::Vector3& a_position) { m_lightData.m_position = a_position; }
    inline void SetDirection(const Maths::Vector3& a_direction) { m_lightData.m_direction = a_direction; }
    inline void SetColor(const Maths::Vector3& a_color) { m_lightData.m_color = a_color; }
    inline void SetIntensity(const float a_intensity) { m_lightData.m_intensity = a_intensity; }
    inline void SetAmbientStrength(const float a_ambientStrength) { m_lightData.m_ambientStrength = a_ambientStrength; }
    inline void SetSpecularStrength(const float a_specularStrength) { m_lightData.m_specularStrength = a_specularStrength; }
    inline void SetType(const LightType a_type) { m_lightData.m_type = a_type; }


private:
    LightData m_lightData {};
    bool m_isActive { true };
};