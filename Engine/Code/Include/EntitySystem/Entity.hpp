#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "EntityComponent.hpp"
#include "Logger.hpp"

class EntityManager;

class Entity
{
public:
    explicit Entity(EntityManager& manager) :
        entityManager(manager) {}

    void SetName(const std::string& a_newName)
    {
        name = a_newName;
    }

    [[nodiscard]] std::string GetName() const
    {
        return name;
    }

    void AddComponent(const std::shared_ptr<void>& component)
    {
        m_components.push_back(component);
    }

    template<typename T>
    [[nodiscard]] std::shared_ptr<T> GetComponent() const
    {
        typename std::vector<std::shared_ptr<void>>::const_iterator it;
        for (it = m_components.cbegin(); it != m_components.cend(); ++it)
        {
            std::shared_ptr<T> casted = std::dynamic_pointer_cast<T>(*it);
            if (casted != nullptr)
            {
                return casted;
            }
        }
        return nullptr;
    }

    void AddLogic(const std::shared_ptr<EntityComponent>& logic)
    {
        m_entityComponents.push_back(logic);
    }

    [[nodiscard]] bool HasChildren() const
    {
        return !m_children.empty();
    }

    void AttachChild(const std::shared_ptr<Entity>& child)
    {
        m_children.push_back(child);
    }

    [[nodiscard]] std::vector<std::shared_ptr<Entity>> GetChildren() const
    {
        return m_children;
    }

    void SetParent(const std::shared_ptr<Entity>& a_parentEntity)
    {
        m_parent = a_parentEntity;
    }

    [[nodiscard]] std::shared_ptr<Entity> GetParent() const
    {
        return m_parent;
    }

    [[nodiscard]] bool HasParent() const
    {
        return m_parent != nullptr;
    }

    void Initialize()
    {
        std::vector<std::shared_ptr<EntityComponent>>::iterator logicIt;
        for (logicIt = m_entityComponents.begin(); logicIt != m_entityComponents.end(); ++logicIt)
        {
            (*logicIt)->Initialize();
        }

        std::vector<std::shared_ptr<Entity>>::iterator childIt;
        for (childIt = m_children.begin(); childIt != m_children.end(); ++childIt)
        {
            (*childIt)->Initialize();
        }
    }

    void GameplayStarted()
    {
        std::vector<std::shared_ptr<EntityComponent>>::iterator logicIt;
        for (logicIt = m_entityComponents.begin(); logicIt != m_entityComponents.end(); ++logicIt)
        {
            (*logicIt)->GameplayStarted();
        }

        std::vector<std::shared_ptr<Entity>>::iterator childIt;
        for (childIt = m_children.begin(); childIt != m_children.end(); ++childIt)
        {
            (*childIt)->GameplayStarted();
        }
    }

    void Update()
    {
        std::vector<std::shared_ptr<EntityComponent>>::iterator logicIt;
        for (logicIt = m_entityComponents.begin(); logicIt != m_entityComponents.end(); ++logicIt)
        {
            (*logicIt)->Update();
        }

        std::vector<std::shared_ptr<Entity>>::iterator childIt;
        for (childIt = m_children.begin(); childIt != m_children.end(); ++childIt)
        {
            (*childIt)->Update();
        }
    }

private:
    EntityManager& entityManager;
    std::string name = "Entity";

    std::vector<std::shared_ptr<void>> m_components;
    std::vector<std::shared_ptr<EntityComponent>> m_entityComponents;
    std::vector<std::shared_ptr<Entity>> m_children;
    std::shared_ptr<Entity> m_parent;
};

class EntityManager
{
public:
    [[nodiscard]] std::shared_ptr<Entity> CreateEntity()
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>(*this);
        entities.push_back(entity);
        return entity;
    }

    void RegisterLogic(const std::shared_ptr<EntityComponent>& a_logic)
    {
        logicComponents.push_back(a_logic);
    }

    void Initialize()
    {
        std::vector<std::shared_ptr<EntityComponent>>::iterator logicIt;
        for (logicIt = logicComponents.begin(); logicIt != logicComponents.end(); ++logicIt)
        {
            (*logicIt)->Initialize();
        }

        std::vector<std::shared_ptr<Entity>>::iterator entityIt;
        for (entityIt = entities.begin(); entityIt != entities.end(); ++entityIt)
        {
            (*entityIt)->Initialize();
        }
    }

    void GameplayStarted()
    {
        std::vector<std::shared_ptr<EntityComponent>>::iterator logicIt;
        for (logicIt = logicComponents.begin(); logicIt != logicComponents.end(); ++logicIt)
        {
            (*logicIt)->GameplayStarted();
        }

        std::vector<std::shared_ptr<Entity>>::iterator entityIt;
        for (entityIt = entities.begin(); entityIt != entities.end(); ++entityIt)
        {
            (*entityIt)->GameplayStarted();
        }
    }

    void Update()
    {
        std::vector<std::shared_ptr<EntityComponent>>::iterator logicIt;
        for (logicIt = logicComponents.begin(); logicIt != logicComponents.end(); ++logicIt)
        {
            (*logicIt)->Update();
        }

        std::vector<std::shared_ptr<Entity>>::iterator entityIt;
        for (entityIt = entities.begin(); entityIt != entities.end(); ++entityIt)
        {
            (*entityIt)->Update();
        }
    }

private:
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<EntityComponent>> logicComponents;
};
