#include <iostream>
#include <cstdarg>
#include <thread>


#include "Struct/Vertex.hpp"

#include "jolt/Jolt/Jolt.h"


#include "jolt/Jolt/Physics/Collision/ObjectLayer.h"
#include "jolt/Jolt/Core/Factory.h"
#include "jolt/Jolt/Core/JobSystemThreadPool.h"
#include "jolt/Jolt/Core/TempAllocator.h"
#include "jolt/Jolt/Physics/Body/BodyActivationListener.h"
#include "jolt/Jolt/Physics/Body/BodyCreationSettings.h"
#include "jolt/Jolt/Physics/Collision/Shape/BoxShape.h"
#include "jolt/Jolt/Physics/Collision/Shape/SphereShape.h"
#include "jolt/Jolt/Physics/PhysicsSettings.h"
#include "jolt/Jolt/Physics/PhysicsSystem.h"
#include "jolt/Jolt/RegisterTypes.h"
#include "jolt/Physics/PhysicsScene.h"


JPH_NAMESPACE_BEGIN



class MyContactListener : public ContactListener
{
public:
    virtual ValidateResult OnContactValidate(const Body& inBody1, const Body& inBody2, RVec3Arg inBaseOffset, const CollideShapeResult& inCollisionResult) override;


    virtual void OnContactAdded(const Body& inBody1, const Body& inBody2, const ContactManifold& inManifold, ContactSettings& ioSettings) override;

    virtual void OnContactPersisted(const Body& inBody1, const Body& inBody2, const ContactManifold& inManifold, ContactSettings& ioSettings) override;


    virtual void OnContactRemoved(const SubShapeIDPair& inSubShapePair) override;
};


class MyBodyActivationListener : public BodyActivationListener
{
public:
    virtual void OnBodyActivated(const BodyID& inBodyID, uint64 inBodyUserData) override;

    virtual void OnBodyDeactivated(const BodyID& inBodyID, uint64 inBodyUserData) override;

};

JPH_NAMESPACE_END