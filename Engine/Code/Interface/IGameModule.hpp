#pragma once


class IGameModule
{
public:
    virtual ~IGameModule() = default;
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void LateUpdate() = 0;
    virtual void FixedUpdate() = 0;
    virtual void End() = 0;
};