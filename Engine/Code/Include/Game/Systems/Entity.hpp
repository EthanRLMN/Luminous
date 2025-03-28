#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "Transform.hpp"

class Entity
{
public:
    Entity() = default;
    ~Entity() = default;

    template<typename T, typename... Args>
    std::shared_ptr<T> AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of_v<Component, T>, "T must inherit from a component!");
        auto l_component = std::make_shared<T>(std::forward<Args>(args)...);
        m_components[typeid(T)] = l_component;

        return l_component;
    }

    template <typename T>
    void RemoveComponent()
    {
        static_assert(std::is_base_of_v<Component, T>, "T must inherit from a component!");
        const auto it = m_components.find(typeid(T));
        if (it != m_components.end()) { m_components.erase(it); }
    }

    template<typename T>
    std::shared_ptr<T> GetComponent()
    {
        const auto it = m_components.find(typeid(T));
        if (it != m_components.end()) { return std::static_pointer_cast<T>(it->second); }

        return nullptr;
    }


    Transform m_transform;


private:
    void Update();

    std::unordered_map<std::type_index, std::shared_ptr<Component>> m_components { };
};
