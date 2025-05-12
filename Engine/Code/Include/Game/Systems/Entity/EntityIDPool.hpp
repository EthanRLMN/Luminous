#pragma once

#include <random>
#include <set>


using EntityID = uint32_t; // Global Alias for entity ids

class EntityIDPool
{
public:
    using EntityID = uint32_t;

    inline EntityID Generate()
    {
        EntityID l_id{ 0 };

        while (m_usedIds.contains(l_id))
            l_id = m_distributor(m_randomVal);

        m_usedIds.insert(l_id);
        return l_id;
    }

    inline void Release(const EntityID& a_id)
    {
        m_usedIds.erase(a_id);
    }


private:
    std::set<EntityID> m_usedIds{};
    std::mt19937 m_randomVal{ std::random_device{}() };
    std::uniform_int_distribution<EntityID> m_distributor{ 1, std::numeric_limits<EntityID>::max() };
};
