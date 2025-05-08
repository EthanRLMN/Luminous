#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "Entity.hpp"
#include "EntityComponent.hpp" 

class Engine;

class EntityManager
{
public:

    [[nodiscard]] inline const std::vector<std::shared_ptr<Entity>>& GetEntities() const { return m_entities; }
    [[nodiscard]] inline const std::vector<std::shared_ptr<EntityComponent>>& GetLogicComponents() const { return m_logicComponents; }
    [[nodiscard]] inline bool HasEntityByName(const std::string& a_name) const { return GetEntityByName(a_name) != nullptr; }

    inline void RegisterLogic(const std::shared_ptr<EntityComponent>& a_logic) { m_logicComponents.push_back(a_logic); }

    [[nodiscard]] inline std::shared_ptr<Entity> CreateEntity()
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(*this);
        m_entities.push_back(l_entity);
        return l_entity;
    }

    inline void Initialize(Engine* a_engine) 
    {
        m_engine = a_engine;
        for (const std::shared_ptr<EntityComponent>& l_logic : m_logicComponents) 
        {
            l_logic.get()->m_engine = a_engine;
            l_logic->Initialize();
        }
            
        for (const std::shared_ptr<Entity>& l_entity : m_entities)
        {
            l_entity.get()->m_engine = a_engine;
            l_entity->Initialize();
        }
    }


    inline void GameplayStarted() const
    {
        for (const std::shared_ptr<EntityComponent>& l_logic : m_logicComponents)
            l_logic->GameplayStarted();

        for (const std::shared_ptr<Entity>& l_entity : m_entities)
            l_entity->GameplayStarted();
    }


    inline void Update() const
    {
        for (const std::shared_ptr<EntityComponent>& l_logic : m_logicComponents)
            l_logic->Update();

        for (const std::shared_ptr<Entity>& l_entity : m_entities)
            l_entity->Update();
    }


    [[nodiscard]] inline std::shared_ptr<Entity> GetEntityByName(const std::string& a_name) const
    {
        for (const std::shared_ptr<Entity>& l_entity : m_entities)
        {
            if (l_entity->GetName() == a_name)
                return l_entity;
        }
        return nullptr;
    }


    [[nodiscard]] inline std::shared_ptr<Entity> GetFirstEntityByParent(const std::shared_ptr<Entity>& a_parent) const
    {
        for (const std::shared_ptr<Entity>& l_entity : m_entities)
        {
            if (l_entity->GetParent() == a_parent)
                return l_entity;
        }
        return nullptr;
    }


    [[nodiscard]] inline std::shared_ptr<Entity> GetEntityByComponent(const std::shared_ptr<EntityComponent>& a_component) const
    {
        for (const std::shared_ptr<Entity>& l_entity : m_entities)
        {
            if (l_entity->GetComponent<EntityComponent>() == a_component)
                return l_entity;
        }
        return nullptr;
    }


    template<typename T>
    [[nodiscard]] inline std::vector<std::shared_ptr<Entity>> GetEntitiesByComponent() const
    {
        std::vector<std::shared_ptr<Entity>> entitiesWithComponent;

        for (const std::shared_ptr<Entity>& l_entity : m_entities)
        {
            auto component = l_entity->GetComponent<T>();
            if (component)
            {
                entitiesWithComponent.push_back(l_entity); 
            }
        }
        return entitiesWithComponent; 
    }

    
    inline void RemoveEntity(const std::shared_ptr<Entity>& a_entity) { std::erase(m_entities, a_entity); }

    inline void RemoveEntityByName(const std::string& a_name)
    {
        std::erase_if(m_entities, [&](const std::shared_ptr<Entity>& l_entity)
                      { return l_entity->GetName() == a_name; });
    }


    inline void RemoveEntityByComponent(const std::shared_ptr<EntityComponent>& a_component)
    {
        std::erase_if(m_entities, [&](const std::shared_ptr<Entity>& l_entity)
                      { return l_entity->GetComponent<EntityComponent>() == a_component; });
    }

    inline void Destroy()
    {
        m_entities.clear();
        m_logicComponents.clear();
    }

    [[nodiscard]] inline size_t GetEntityCount() const { return m_entities.size(); }
    [[nodiscard]] inline size_t GetLogicComponentCount() const { return m_logicComponents.size(); }
    [[nodiscard]] inline bool IsEmpty() const { return m_entities.empty(); }
    [[nodiscard]] inline bool HasEntity(const std::shared_ptr<Entity>& a_entity) const { return std::ranges::find(m_entities, a_entity) != m_entities.end(); }

    Engine* m_engine{ nullptr };
    
private:
    std::vector<std::shared_ptr<Entity>> m_entities; 
    std::vector<std::shared_ptr<EntityComponent>> m_logicComponents; 
};
