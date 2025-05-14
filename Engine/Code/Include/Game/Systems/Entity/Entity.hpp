#pragma once

#include <memory>
#include <string>
#include <vector>

#include "EntityIDPool.hpp"
#include "Game/Systems/Component/EntityComponent.hpp"
#include "Game/Systems/Component/TransformComponent.hpp"
#include "Game/Systems/Component/ModelComponent.hpp"
#include "Game/Systems/Physics/RigidBody.hpp"

class EntityManager;

class Entity : public std::enable_shared_from_this<Entity>
{
public:
    explicit Entity(EntityManager& a_manager) : m_entityManager(a_manager) {}
    void Initialize() const;
    void GameplayStarted() const;
    void Update() const;

    inline Engine* GetEngine() const { return m_engine; }
    inline EntityManager& GetEntityManager() const { return m_entityManager; }
    inline uint16_t GetUUID() const { return m_uuid; }

    template<typename T>
    [[nodiscard]] inline std::shared_ptr<T> GetComponent() const
    {
        for (const std::shared_ptr<EntityComponent>& component : m_components)
        {
            std::shared_ptr<T> l_casted = std::dynamic_pointer_cast<T>(component);
            if (l_casted)
                return l_casted;
        }
        return nullptr;
    }


    [[nodiscard]] inline std::string GetName() const { return m_name; }
    [[nodiscard]] inline bool IsActive() const { return m_isActive; }

    inline void SetEngine(Engine* a_engine) { m_engine = a_engine; }
    inline void SetName(const std::string& a_newName) { m_name = a_newName; }
    inline void SetUUID(const EntityID a_uuid) { m_uuid = a_uuid; }
    inline void AddComponent(const std::shared_ptr<EntityComponent>& a_component) { m_components.push_back(a_component); }

    inline std::shared_ptr<ModelComponent> Model() const { return GetComponent<ModelComponent>(); }
    inline std::shared_ptr<TransformComponent> Transform() const { return GetComponent<TransformComponent>(); }

    void SetActive(bool a_isActive);


private:
    Engine* m_engine { nullptr };
    EntityManager& m_entityManager;
    std::string m_name { };

    std::vector<std::shared_ptr<EntityComponent>> m_components { };

    EntityID m_uuid { 0 };
    bool m_isActive { true };
};