#pragma once

class ComponentSystem
{
public:
    virtual ~ComponentSystem() = default;
    virtual void Update() {}
};
