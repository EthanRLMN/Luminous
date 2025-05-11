#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Game/Systems/Component/EntityComponent.hpp"
#include "Game/Systems/Physics/RigidBody.hpp"
#include "Game/Systems/Component/TransformComponent.hpp"

class EntityManager;


class Entity : public std::enable_shared_from_this<Entity>
{
public:
    inline explicit Entity(EntityManager& a_manager) : m_entityManager(a_manager) {}
    void Initialize() const;
    void GameplayStarted() const;
    void Update() const;

    inline Engine* GetEngine() const { return m_engine; }
    inline EntityManager& GetEntityManager() const { return m_entityManager; }

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

    std::vector<std::shared_ptr<Entity>> GetEntitiesWithModelComponent() const;
    [[nodiscard]] inline std::string GetName() const { return m_name; }
    [[nodiscard]] inline bool IsActive() const { return m_isActive; }


    inline void SetEngine(Engine* a_engine) { m_engine = a_engine; }
    inline void SetName(const std::string& a_newName) { m_name = a_newName; }
    inline void AddComponent(const std::shared_ptr<EntityComponent>& a_component) { m_components.push_back(a_component); }
    inline std::shared_ptr<TransformComponent> Transform() const { return GetComponent<TransformComponent>(); }
    void SetActive(bool a_isActive);


private:
    Engine* m_engine { nullptr };
    EntityManager& m_entityManager;
    std::string m_name { };

    std::vector<std::shared_ptr<EntityComponent>> m_components { };
    std::vector<std::shared_ptr<Entity>> m_entities { };

    bool m_isActive { true };
};