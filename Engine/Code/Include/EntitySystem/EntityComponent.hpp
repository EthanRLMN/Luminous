#pragma once

class EntityComponent
{
public:
    virtual ~EntityComponent() = default;

    virtual void Create() = 0;
    virtual void Destroy() = 0;
    virtual void Update() = 0;
};