#pragma once

#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>

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


    std::string entityName = "default";
};

class EntityManager
{
private:
    std::unordered_map<size_t, Entity> entities;
    size_t nextEntityId = 0;

public:
    size_t CreateEntity()
    {
        Entity l_entity;
        size_t l_id = nextEntityId++;
        entities[l_id] = std::move(l_entity);
        return l_id;
    }

    void DestroyEntity(size_t _id)
    {
        entities.erase(_id);
    }

    Entity& GetEntity(size_t _id)
    {
        return entities.at(_id);
    }
};
