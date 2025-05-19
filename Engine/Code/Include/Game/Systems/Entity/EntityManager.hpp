#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "Game/Systems/Component/EntityComponent.hpp"
#include "Game/Systems/Entity/Entity.hpp"

class MeshRendererComponent;
class Engine;

class EntityManager
{
public:
    EntityManager() = default;
    ~EntityManager() = default;

    void Initialize(Engine* a_engine);
    void Update() const;
    void GameplayStarted() const;

    inline void RegisterRenderable(const std::shared_ptr<Entity>& a_entity) { m_renderableEntities.push_back(a_entity); }
    inline void UnregisterRenderable(const std::shared_ptr<Entity>& a_entity) { std::erase(m_renderableEntities, a_entity); }
    inline void RegisterLight(const std::shared_ptr<Entity>& a_entity) { m_lightEntities.push_back(a_entity); }
    inline void UnregisterLight(const std::shared_ptr<Entity>& a_entity) { std::erase(m_lightEntities, a_entity); }

    /*          Getters         */
    inline const std::vector<std::shared_ptr<Entity> >& GetEntities() const { return m_entities; }
    inline bool HasEntityByName(const std::string& a_name) const { return GetEntityByName(a_name) != nullptr; }
    inline size_t GetEntityCount() const { return m_entities.size(); }
    inline bool IsEmpty() const { return m_entities.empty(); }
    inline bool HasEntity(const std::shared_ptr<Entity>& a_entity) const { return std::ranges::find(m_entities, a_entity) != m_entities.end(); }
    inline const std::vector<std::shared_ptr<Entity>>& GetRenderableEntities() const { return m_renderableEntities; }
    inline const std::vector<std::shared_ptr<Entity>>& GetLightEntities() const { return m_lightEntities; }
    std::shared_ptr<Entity> GetEntityByName(const std::string& a_name) const;
    std::shared_ptr<Entity> GetFirstEntityByParent(const std::shared_ptr<Entity>& a_parent) const;
    [[nodiscard]] std::shared_ptr<Entity> GetEntityByRawPointer(const Entity* rawPtr) const;
    static std::vector<std::string> GetAvailableTemplates();
    Engine* GetEngine() const { return m_engine; }

    void DestroyLightEntities();
    void DestroyRenderableEntities();
    void DestroyAllEntities();

    template<typename T>
    inline std::vector<std::shared_ptr<Entity> > GetEntitiesByComponent() const
    {
        std::vector<std::shared_ptr<Entity> > l_entitiesWithComponent{};

        for (const std::shared_ptr<Entity>& l_entity : m_entities)
        {
            std::shared_ptr<T> l_component = l_entity->GetComponent<T>();
            if (l_component)
                l_entitiesWithComponent.push_back(l_entity);
        }
        return l_entitiesWithComponent;
    }


    /*          Setters         */
    inline void RemoveEntity(const std::shared_ptr<Entity>& a_entity) { std::erase(m_entities, a_entity); }
    inline void RemoveEntityByName(const std::string& a_name) { std::erase_if(m_entities, [&](const std::shared_ptr<Entity>& l_entity) { return l_entity->GetName() == a_name; }); }
    inline void Destroy() { m_entities.clear(); }
    std::shared_ptr<Entity> CreateEntityFromTemplate(const std::string& a_templateName);


private:
    Engine* m_engine{ nullptr };
    std::vector<std::shared_ptr<Entity>> m_entities{};
    std::vector<std::shared_ptr<Entity>> m_renderableEntities{};
    std::vector<std::shared_ptr<Entity>> m_lightEntities{};
};
