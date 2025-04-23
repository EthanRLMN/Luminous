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

    /*
    virtual void Awake() = 0;
    virtual void BeginPlay() = 0;
    virtual void Update() = 0;
    virtual void Destroy(){ isDestroyed = true; }*/
};

class EntityManager
{
private:
    std::unordered_map<size_t, Entity> entities;
    size_t nextEntityId = 0;

public:
    size_t CreateEntity()
    {
        Entity entity;
        size_t id = nextEntityId++;
        entities[id] = std::move(entity);
        return id;
    }

    void DestroyEntity(size_t id)
    {
        entities.erase(id);
    }

    Entity& GetEntity(size_t id)
    {
        return entities.at(id);
    }
};
