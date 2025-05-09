#pragma once

#include <iostream>

#include "jolt/Jolt/Jolt.h"
#include "jolt/Jolt/Physics/Body/BodyActivationListener.h"


class PhysicsBodyActivationListener final : public JPH::BodyActivationListener
{
public:
    inline void OnBodyActivated(const JPH::BodyID& a_inBodyID, JPH::uint64 a_inBodyUserData) override { static_cast<void>(a_inBodyID); static_cast<void>(a_inBodyUserData); std::cout << "\nA body got activated\n"; };
    inline void OnBodyDeactivated(const JPH::BodyID& a_inBodyID, JPH::uint64 a_inBodyUserData) override { static_cast<void>(a_inBodyID); static_cast<void>(a_inBodyUserData); std::cout << "\nA body went to sleep\n"; };
};
