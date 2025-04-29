#pragma once

#include "EntitySystem/EntityComponent.hpp"
#include "Rendering/Camera/Camera.hpp"

class CameraComponent : public Camera, public EntityComponent
{
public:
    CameraComponent() = default;

    void Create() override {};
    void Destroy() override {};
    void Update() override {};
};
