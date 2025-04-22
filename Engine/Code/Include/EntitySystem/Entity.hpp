#pragma once

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

    virtual void Awake() = 0;
    virtual void BeginPlay() = 0;
    virtual void Update() = 0;
    virtual void Destroy(){ isDestroyed = true; }
};
