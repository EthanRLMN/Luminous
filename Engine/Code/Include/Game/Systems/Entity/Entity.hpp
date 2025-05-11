#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Matrix4.hpp"
#include "Quaternion.hpp"
#include "Vector3.hpp"

#include "Game/Systems/Component/EntityComponent.hpp"
#include "Game/Systems/Physics/RigidBody.hpp"

class EntityManager;


class Entity : public std::enable_shared_from_this<Entity>
{
public:
    inline explicit Entity(EntityManager& a_manager) : m_entityManager(a_manager) {}
    void Initialize() const;
    void GameplayStarted() const;
    void Update() const;

    Engine* GetEngine() const { return m_engine; }
    EntityManager& GetEntityManager() const { return m_entityManager; }
    Maths::Vector3 GetPosition() const { return m_position; }
    Maths::Quaternion GetRotation() const { return m_rotation; }
    Maths::Vector3 GetScale() const { return m_scale; }
    Maths::Matrix4 GetTRS() const { return TRS; }

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
    [[nodiscard]] inline std::vector<std::shared_ptr<Entity>> GetChildren() const { return m_children; }
    [[nodiscard]] inline std::shared_ptr<Entity> GetParent() const { return m_parent; }
    [[nodiscard]] inline bool HasChildren() const { return !m_children.empty(); }
    [[nodiscard]] inline bool HasParent() const { return m_parent != nullptr; }

    void SetEngine(Engine* a_engine) { m_engine = a_engine; }
    inline void SetName(const std::string& a_newName) { m_name = a_newName; }
    inline void AddComponent(const std::shared_ptr<EntityComponent>& a_component) { m_components.push_back(a_component); }
    inline void AttachChild(const std::shared_ptr<Entity>& a_child) { m_children.push_back(a_child); a_child->SetParent(shared_from_this()); }
    inline void SetParent(const std::shared_ptr<Entity>& a_parentEntity) { m_parent = a_parentEntity; }
    inline void SetPosition(const Maths::Vector3 a_position) { m_position = a_position; }
    inline void SetRotation(const Maths::Quaternion a_rotation) { m_rotation = a_rotation; }
    inline void SetScale(const Maths::Vector3 a_scale) { m_scale = a_scale; }
    inline void SetTRS(const Maths::Matrix4& a_TRS) { TRS = a_TRS; }


private:
    Engine* m_engine { nullptr };

    EntityManager& m_entityManager;
    std::string m_name { };

    std::vector<std::shared_ptr<EntityComponent>> m_components { };
    std::vector<std::shared_ptr<Entity>> m_children { };
    std::shared_ptr<Entity> m_parent { nullptr };

    std::vector<std::shared_ptr<Entity>> m_entities { };

    Maths::Vector3 m_position { Maths::Vector3::Zero };
    Maths::Quaternion m_rotation { Maths::Quaternion::Zero };
    Maths::Vector3 m_scale { Maths::Vector3::One };

    Maths::Matrix4 TRS { Maths::Matrix4::TRS(m_position, m_rotation.ToEulerAngles(true), m_scale) };
};