#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <type_traits>
#include <algorithm>

class EntityComponent
{
public:
    virtual ~EntityComponent() = default;
    virtual void Initialize() = 0;
    virtual void GameplayStarted() = 0;
    virtual void Update() = 0;

};