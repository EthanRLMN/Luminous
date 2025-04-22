#pragma once
#include <iostream>
#include <unordered_map>
#include <typeindex>
#include "EntityComponent.hpp"


class Entity
{
public:
    std::unordered_map<std::type_index, std::unique_ptr<BaseComponent>> components;

    template<typename T>
    void addComponent(std::unique_ptr<T> component)
    {
        components[typeid(T)] = std::move(component);
    }

    template<typename T>
    T* getComponent()
    {
        auto it = components.find(typeid(T));
        if (it != components.end())
        {
            return static_cast<T*>(it->second.get());
        }
        return nullptr; 
    }
};
