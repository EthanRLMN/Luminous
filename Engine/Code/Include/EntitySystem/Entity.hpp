#pragma once
#include <iostream>
#include <unordered_map>
#include <typeindex>
#include "EntityComponent.hpp"


class Entity
{
public:
    bool isDestroyed = false;
    std::unordered_map<std::type_index, std::shared_ptr<EntityComponent>> components;

    template<typename T, typename... Args>
    void AddComponent(Args&&... args)
    {
        components[std::type_index(typeid(T))] = std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    std::shared_ptr<T> GetComponent()
    {
        auto it = components.find(std::type_index(typeid(T)));
        if (it != components.end())
        {
            return std::static_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

    // soft delete plus explicite tu meurs
    void Destroy(){ isDestroyed = true; }
};
