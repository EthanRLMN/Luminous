#pragma once
#include <iostream>
#include "Logger.hpp"
#include <vector>
#include <memory>
#include <algorithm>
#include "EntityComponent.hpp"
#include <string.h>

class EntityManager;

class Entity
{
public:
    Entity(EntityManager& manager) :
        entityManager(manager) {}

    void SetName(const std::string& newName) { name = newName; }
    std::string GetName() const { return name; }

    void AddComponent(const std::shared_ptr<void>& component)
    {
        components.push_back(component);
    }

    template<typename T>
    std::shared_ptr<T> GetComponent() const
    {
        for (auto& comp : components)
        {
            if (auto casted = std::dynamic_pointer_cast<T>(comp))
            {
                return casted;
            }
        }
        return nullptr;
    }

    void AddLogic(const std::shared_ptr<EntityComponent>& logic)
    {
        logicComponents.push_back(logic);
    }

    bool HasChildren() const
    {
        return !children.empty(); 
    }

    void AttachChild(std::shared_ptr<Entity> child)
    {
        children.push_back(child);
    }


    std::vector<std::shared_ptr<Entity>> GetChildren() const
    {
        return children;
    }

    void SetParent(std::shared_ptr<Entity> parentEntity)
    {
        parent = parentEntity;
    }

    std::shared_ptr<Entity> GetParent() const
    {
        return parent;
    }

    bool HasParent() const
    {
        return parent != nullptr;
    }


    void Initialize()
    {
        for (auto& logic : logicComponents)
            logic->Initialize();
        for (auto& child : children)
            child->Initialize();
    }

    void GameplayStarted()
    {
        for (auto& logic : logicComponents)
            logic->GameplayStarted();
        for (auto& child : children)
            child->GameplayStarted();
    }

    void Update()
    {
        for (auto& logic : logicComponents)
            logic->Update();
        for (auto& child : children)
            child->Update();
    }

private:
    EntityManager& entityManager;
    std::string name;
    std::vector<std::shared_ptr<void>> components;
    std::vector<std::shared_ptr<EntityComponent>> logicComponents;
    std::vector<std::shared_ptr<Entity>> children;
    std::shared_ptr<Entity> parent;
};

class EntityManager
{
public:
    std::shared_ptr<Entity> CreateEntity()
    {
        auto entity = std::make_shared<Entity>(*this);
        entities.push_back(entity);
        return entity;
    }

    void RegisterLogic(const std::shared_ptr<EntityComponent>& logic)
    {
        logicComponents.push_back(logic);
    }

    void Initialize()
    {
        for (auto& logic : logicComponents)
            logic->Initialize();
        for (auto& entity : entities)
            entity->Initialize();
    }

    void GameplayStarted()
    {
        for (auto& logic : logicComponents)
            logic->GameplayStarted();
        for (auto& entity : entities)
            entity->GameplayStarted();
    }

    void Update()
    {
        for (auto& logic : logicComponents)
            logic->Update();
        for (auto& entity : entities)
            entity->Update();
    }

private:
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<EntityComponent>> logicComponents;
};
