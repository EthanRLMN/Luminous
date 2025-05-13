#pragma once

#include <functional>
#include <ranges>

#include "EntityManager.hpp"
#include "Logger.hpp"
#include "Game/Systems/Component/TransformComponent.hpp"
#include "Game/Systems/Entity/EntityIDPool.hpp"

class EntityFactory
{
public:
    using Creator = std::function<std::shared_ptr<Entity>(EntityManager&)>;


    inline static EntityFactory& Get()
    {
        static EntityFactory s_instance;
        return s_instance;
    }


    inline std::shared_ptr<Entity> CreateEntity(const std::string& a_name, EntityManager& a_entityManager)
    {
        const auto it = m_creators.find(a_name);
        if (it != m_creators.end())
        {
            const std::shared_ptr<Entity> l_entity = it->second(a_entityManager);
            l_entity->SetUUID(m_idPool.Generate());

            const std::shared_ptr<TransformComponent> l_transform = std::make_shared<TransformComponent>();
            l_entity->AddComponent(l_transform);
            l_transform->SetOwner(l_entity);

            DEBUG_LOG_INFO("Entity [ Name= {} ] - [ UUID={} ] created!", l_entity->GetName(), l_entity->GetUUID());

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

    EntityIDPool m_idPool;
};
