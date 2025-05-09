#pragma once
#include <functional>

#include "EntityManager.hpp"

class EntityFactory
{
public:
    using Creator = std::function<std::shared_ptr<Entity>(EntityManager&)>;

    inline static EntityFactory& Get()
    {
        static EntityFactory s_instance;
        return s_instance;
    }

    inline void RegisterEntity(const std::string& a_name, const Creator& a_creator) { m_creators[a_name] = a_creator; }

    std::shared_ptr<Entity> CreateEntity(const std::string& a_name, EntityManager& a_entityManager) const
    {
        const auto it = m_creators.find(a_name);
        if (it != m_creators.end())
            return it->second(a_entityManager);

        return nullptr;
    };

private:
    std::unordered_map<std::string, Creator> m_creators {};
};
