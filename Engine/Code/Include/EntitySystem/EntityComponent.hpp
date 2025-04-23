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
private:
};