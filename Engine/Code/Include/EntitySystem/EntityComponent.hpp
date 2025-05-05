#pragma once


class EntityComponent
{
public:
    virtual ~EntityComponent() = default;
    virtual void Initialize() = 0;
    virtual void GameplayStarted() = 0;
    virtual void Update() = 0;

};