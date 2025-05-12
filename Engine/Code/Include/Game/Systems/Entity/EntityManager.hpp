#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "Game/Systems/Component/EntityComponent.hpp"
#include "Game/Systems/Entity/Entity.hpp"

class Engine;

class EntityManager
{
public:
    EntityManager() = default;
    ~EntityManager() = default;

    void Initialize(Engine* a_engine);
    void Update() const;
    void GameplayStarted() const;

    [[nodiscard]] inline const std::vector<std::shared_ptr<Entity>>& GetEntities() const { return m_entities; }
    [[nodiscard]] inline bool HasEntityByName(const std::string& a_name) const { return GetEntityByName(a_name) != nullptr; }
    [[nodiscard]] inline size_t GetEntityCount() const { return m_entities.size(); }
    [[nodiscard]] inline bool IsEmpty() const { return m_entities.empty(); }
    [[nodiscard]] inline bool HasEntity(const std::shared_ptr<Entity>& a_entity) const { return std::ranges::find(m_entities, a_entity) != m_entities.end(); }
    [[nodiscard]] static std::vector<std::string> GetAvailableTemplates();

    [[nodiscard]] std::shared_ptr<Entity> GetEntityByName(const std::string& a_name) const;
    [[nodiscard]] std::shared_ptr<Entity> GetFirstEntityByParent(const std::shared_ptr<Entity>& a_parent) const;

    template<typename T>
    [[nodiscard]] inline std::vector<std::shared_ptr<Entity>> GetEntitiesByComponent() const
    {
        std::vector<std::shared_ptr<Entity>> l_entitiesWithComponent{};

        for (const std::shared_ptr<Entity>& l_entity : m_entities)
        {
            std::shared_ptr<T> l_component = l_entity->GetComponent<T>();
            if (l_component)
                l_entitiesWithComponent.push_back(l_entity);
        }
        return l_entitiesWithComponent;
    }

    std::shared_ptr<Entity> CreateEntityFromTemplate(const std::string& a_templateName);
    inline void RemoveEntity(const std::shared_ptr<Entity>& a_entity) { std::erase(m_entities, a_entity); }
    inline void RemoveEntityByName(const std::string& a_name) { std::erase_if(m_entities, [&](const std::shared_ptr<Entity>& l_entity) { return l_entity->GetName() == a_name; }); }
    inline void Destroy() { m_entities.clear(); }


private:
    Engine* m_engine { nullptr };

    std::vector<std::shared_ptr<Entity>> m_entities;
};
