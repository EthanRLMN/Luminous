#pragma once

#include <functional>
#include <ranges>

#include "EntityManager.hpp"
#include "Game/Systems/Component/TransformComponent.hpp"

class EntityFactory
{
public:
    using Creator = std::function<std::shared_ptr<Entity>(EntityManager&)>;


    inline static EntityFactory& Get()
    {
        static EntityFactory s_instance;
        return s_instance;
    }


    inline std::shared_ptr<Entity> CreateEntity(const std::string& a_name, EntityManager& a_entityManager) const
    {
        const auto it = m_creators.find(a_name);
        if (it != m_creators.end())
        {
            const std::shared_ptr<Entity> l_entity = it->second(a_entityManager);
            l_entity->AddComponent(std::make_shared<TransformComponent>());
            return l_entity;
        }
        return nullptr;
    }


    [[nodiscard]] inline std::vector<std::string> GetAvailableTemplates() const
    {
        std::vector<std::string> l_result {};

        for (const std::string& l_name : m_creators | std::views::keys)
            l_result.push_back(l_name);

        return l_result;
    }


    inline void RegisterEntity(const std::string& a_name, const Creator& a_creator)
    {
        m_creators[a_name] = a_creator;
    }


private:
    std::unordered_map<std::string, Creator> m_creators {};
};
