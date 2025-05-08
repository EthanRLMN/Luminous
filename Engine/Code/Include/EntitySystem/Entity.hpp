#pragma once

#include <memory>
#include <string>
#include <vector>

#include "EntityComponent.hpp"
#include "Quaternion.hpp"
#include "Vector3.hpp"
#include "Matrix4.hpp"

#include "EntitySystem/Components/ModelComponent.hpp"


class EntityManager;


class Entity : public std::enable_shared_from_this<Entity>
{
public:
    inline explicit Entity(EntityManager& a_manager) : m_engine{ nullptr }, m_entityManager(a_manager) {}

    inline void SetName(const std::string& a_newName) { m_name = a_newName; }
    inline void AddComponent(const std::shared_ptr<void>& a_component) { m_components.push_back(a_component); }
    inline void AddLogic(const std::shared_ptr<EntityComponent>& a_logic) { m_entityComponents.push_back(a_logic); }
    inline void AttachChild(const std::shared_ptr<Entity>& a_child) { m_children.push_back(a_child); a_child->SetParent(shared_from_this()); }
    inline void SetParent(const std::shared_ptr<Entity>& a_parentEntity) { m_parent = a_parentEntity; }


    Maths::Vector3 GetPosition() const { return position; };
    Maths::Quaternion GetRotation() const { return rotation; };
    Maths::Vector3 GetScale() const { return scale; };

    Maths::Matrix4 GetTRS() const { return TRS; };


    void SetPosition(const Maths::Vector3 a_position) { position = a_position; };
    void SetRotation(const Maths::Quaternion a_rotation) { rotation = a_rotation; };
    void SetScale(const Maths::Vector3 a_scale) { scale = a_scale; };

    void SetTRS(const Maths::Matrix4& a_TRS) { TRS = a_TRS; };
    

    [[nodiscard]] inline std::string GetName() const { return m_name; }
    [[nodiscard]] inline std::vector<std::shared_ptr<Entity>> GetChildren() const { return m_children; }
    [[nodiscard]] inline std::shared_ptr<Entity> GetParent() const { return m_parent; }
    [[nodiscard]] inline bool HasChildren() const { return !m_children.empty(); }
    [[nodiscard]] inline bool HasParent() const { return m_parent != nullptr; }
    EntityManager& GetEntityManager() const { return m_entityManager; }

    template<typename T>
    [[nodiscard]] inline std::shared_ptr<T> GetComponent() const
    {
        for (const std::shared_ptr<void>& l_component : m_components)
        {
            std::shared_ptr<T> l_casted = std::static_pointer_cast<T>(l_component);
            if (l_casted != nullptr)
                return l_casted;
        }
        return nullptr;
    }

    std::vector<std::shared_ptr<Entity>> GetEntitiesWithModelComponent() const
    {
        std::vector<std::shared_ptr<Entity>> l_entitiesWithModel;
        for (auto& entity : m_entities)
        { 
            auto modelComponent = entity->GetComponent<ModelComponent>();
            if (modelComponent != nullptr)
                l_entitiesWithModel.push_back(entity);
        }
        return l_entitiesWithModel;
    }

    inline void Initialize() const
    {
        for (const std::shared_ptr<EntityComponent>& l_logic : m_entityComponents) 
        {
            l_logic.get()->m_engine = m_engine;
            l_logic->Initialize();
        }
            

        for (const std::shared_ptr<Entity>& l_child : m_children)
        {
            l_child.get()->m_engine = m_engine;
            l_child->Initialize();
        }
    }


    inline void GameplayStarted() const
    {
        for (const std::shared_ptr<EntityComponent>& l_logic : m_entityComponents)
            l_logic->GameplayStarted();

        for (const std::shared_ptr<Entity>& l_child : m_children)
            l_child->GameplayStarted();
    }


    inline void Update() const
    {
        for (const std::shared_ptr<EntityComponent>& l_logic : m_entityComponents)
            l_logic->Update();

        for (const std::shared_ptr<Entity>& l_child : m_children)
            l_child->Update();
    }


    Engine* m_engine;

private:
    EntityManager& m_entityManager;
    std::string m_name { };

    // TODO : Use a generic virtual component so that we can replace `void` with the actual component type, making the system faster and safer
    std::vector<std::shared_ptr<void>> m_components { };
    std::vector<std::shared_ptr<EntityComponent>> m_entityComponents { };
    std::vector<std::shared_ptr<Entity>> m_children { };
    std::shared_ptr<Entity> m_parent { nullptr };

    std::vector<std::shared_ptr<Entity>> m_entities{};

    Maths::Vector3 position = Maths::Vector3::Zero;
    Maths::Quaternion rotation = Maths::Quaternion::Zero;
    Maths::Vector3 scale = Maths::Vector3::One;

    Maths::Matrix4 TRS = Maths::Matrix4::TRS(position, rotation.ToEulerAngles(true), scale);

    
};
