#pragma once

#include <memory>

class RigidbodyComponent;


class ICollisionListener
{
public:
    virtual ~ICollisionListener() = default;
    virtual void OnCollisionEnter(std::shared_ptr<RigidbodyComponent> a_self, std::shared_ptr<RigidbodyComponent> a_other) = 0;
    virtual void OnCollisionStay(std::shared_ptr<RigidbodyComponent> a_self, std::shared_ptr<RigidbodyComponent> a_other) = 0;
    virtual void OnCollisionExit(std::shared_ptr<RigidbodyComponent> a_self, std::shared_ptr<RigidbodyComponent> a_other) = 0;
};
