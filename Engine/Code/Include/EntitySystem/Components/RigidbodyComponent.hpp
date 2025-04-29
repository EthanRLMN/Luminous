#pragma once

#include "EntitySystem/EntityComponent.hpp"


class RigidbodyComponent : public EntityComponent
{
public:
    RigidbodyComponent() = default;
    ~RigidbodyComponent() override = default;

    void Create() override {};
    void Destroy() override {};
    void Update() override {};

private:

};
