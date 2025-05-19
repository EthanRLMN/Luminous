#pragma once

#include "IGameModule.hpp"


class GameModuleImpl : public IGameModule
{
public:
    GameModuleImpl() = default;
    ~GameModuleImpl() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;
    void FixedUpdate() override;
    void End() override;
};
