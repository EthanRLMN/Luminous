#pragma once

#include <iostream>

#include "jolt/Jolt/Jolt.h"
#include "jolt/Jolt/Physics/Body/BodyActivationListener.h"


class PhysicsBodyActivationListener final : public JPH::BodyActivationListener
{
public:
    virtual inline void OnBodyActivated(const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData) override { std::cout << "\nA body got activated\n"; };
    virtual inline void OnBodyDeactivated(const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData) override { std::cout << "\nA body went to sleep\n"; };
};
