#pragma once
#include <memory>
#include <vector>

#include "Game/Systems/Physics/PhysicsCollisionListener.hpp"

/*
class RigidbodyComponent : public std::enable_shared_from_this<RigidbodyComponent>
{
public:
    inline void AddCollisionListener(const std::shared_ptr<ICollisionListener>& a_listener) { m_listeners.push_back(a_listener); }

    void NotifyCollisionEnter(const std::shared_ptr<RigidbodyComponent>& a_other)
    {
        for (const std::shared_ptr<ICollisionListener>& l_listener : m_listeners)
            l_listener->OnCollisionEnter(shared_from_this(), a_other);
    }

    void NotifyCollisionStay(const std::shared_ptr<RigidbodyComponent>& a_other)
    {
        for (const std::shared_ptr<ICollisionListener>& l_listener : m_listeners)
            l_listener->OnCollisionStay(shared_from_this(), a_other);
    }

    void NotifyCollisionExit(const std::shared_ptr<RigidbodyComponent>& a_other)
    {
        for (const std::shared_ptr<PhysicsCollisionListener>& l_listener : m_listeners)
            l_listener->OnColl(shared_from_this(), a_other);
    }


    bool IsSimulatingPhysics() const { return m_simulatePhysics; }
    void SetSimulatingPhysics(const bool a_value) { m_simulatePhysics = a_value; }


private:
    std::vector<std::shared_ptr<ICollisionListener>> m_listeners { };
    bool m_simulatePhysics { true };
};
*/