
#include "Logger.hpp"
#include <iostream>

#include "Struct/Vertex.hpp"

#include "jolt/Jolt/Jolt.h"


#include "jolt/Jolt/RegisterTypes.h"
#include "jolt/Jolt/Core/Factory.h"
#include "jolt/Jolt/Core/TempAllocator.h"
#include "jolt/Jolt/Core/JobSystemThreadPool.h"
#include "jolt/Jolt/Physics/PhysicsSettings.h"
#include "jolt/Jolt/Physics/PhysicsSystem.h"
#include "jolt/Jolt/Physics/Collision/Shape/BoxShape.h"
#include "jolt/Jolt/Physics/Collision/Shape/SphereShape.h"
#include "jolt/Jolt/Physics/Body/BodyCreationSettings.h"
#include "jolt/Jolt/Physics/Body/BodyActivationListener.h"
#include "jolt/Physics/PhysicsScene.h"


using namespace JPH;




class Physics
{
public:
    Physics() {};
    ~Physics() {};

    void Init_JOLT();
    void Update_JOLT(float _deltaTime);
    void Clean_JOLT();

    JPH::Body* CreateBody(float _radius);
   
    
    
private:
    JPH::PhysicsSystem* m_physicsSystem = nullptr; 
    JPH::BodyInterface* m_bodyInterface = nullptr;
};


namespace Layers
{
    static constexpr ObjectLayer NON_MOVING = 0;
    static constexpr ObjectLayer MOVING = 1;
    static constexpr ObjectLayer NUM_LAYERS = 2;
}; // namespace Layers


class ObjectLayerPairFilterImpl : public ObjectLayerPairFilter
{
public:
    virtual bool ShouldCollide(ObjectLayer inObject1, ObjectLayer inObject2) const override
    {
        switch (inObject1)
        {
            case Layers::NON_MOVING:
                return inObject2 == Layers::MOVING; // Non moving only collides with moving
            case Layers::MOVING:
                return true; // Moving collides with everything
            default:
                JPH_ASSERT(false);
                return false;
        }
    }
};

// Each broadphase layer results in a separate bounding volume tree in the broad phase. You at least want to have
// a layer for non-moving and moving objects to avoid having to update a tree full of static objects every frame.
// You can have a 1-on-1 mapping between object layers and broadphase layers (like in this case) but if you have
// many object layers you'll be creating many broad phase trees, which is not efficient. If you want to fine tune
// your broadphase layers define JPH_TRACK_BROADPHASE_STATS and look at the stats reported on the TTY.
namespace BroadPhaseLayers
{
    static constexpr BroadPhaseLayer NON_MOVING(0);
    static constexpr BroadPhaseLayer MOVING(1);
    static constexpr uint NUM_LAYERS(2);
}; // namespace BroadPhaseLayers

// BroadPhaseLayerInterface implementation
// This defines a mapping between object and broadphase layers.
class BPLayerInterfaceImpl final : public BroadPhaseLayerInterface
{
public:
    BPLayerInterfaceImpl()
    {
        // Create a mapping table from object to broad phase layer
        mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
        mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
    }

    virtual uint GetNumBroadPhaseLayers() const override
    {
        return BroadPhaseLayers::NUM_LAYERS;
    }

    virtual BroadPhaseLayer GetBroadPhaseLayer(ObjectLayer inLayer) const override
    {
        JPH_ASSERT(inLayer < Layers::NUM_LAYERS);
        return mObjectToBroadPhase[inLayer];
    }


private:
    BroadPhaseLayer mObjectToBroadPhase[Layers::NUM_LAYERS];
};

/// Class that determines if an object layer can collide with a broadphase layer
class ObjectVsBroadPhaseLayerFilterImpl : public ObjectVsBroadPhaseLayerFilter
{
public:
    virtual bool ShouldCollide(ObjectLayer inLayer1, BroadPhaseLayer inLayer2) const override
    {
        switch (inLayer1)
        {
            case Layers::NON_MOVING:
                return inLayer2 == BroadPhaseLayers::MOVING;
            case Layers::MOVING:
                return true;
            default:
                JPH_ASSERT(false);
                return false;
        }
    }
};

// An example contact listener
class MyContactListener : public ContactListener
{
public:
    // See: ContactListener
    virtual ValidateResult OnContactValidate(const Body& inBody1, const Body& inBody2, RVec3Arg inBaseOffset, const CollideShapeResult& inCollisionResult) override
    {
        std::cout << "Contact validate callback" << std::endl;

        // Allows you to ignore a contact before it is created (using layers to not make objects collide is cheaper!)
        return ValidateResult::AcceptAllContactsForThisBodyPair;
    }

    virtual void OnContactAdded(const Body& inBody1, const Body& inBody2, const ContactManifold& inManifold, ContactSettings& ioSettings) override
    {
        std::cout << "A contact was added" << std::endl;
    }

    virtual void OnContactPersisted(const Body& inBody1, const Body& inBody2, const ContactManifold& inManifold, ContactSettings& ioSettings) override
    {
        std::cout << "A contact was persisted" << std::endl;
    }

    virtual void OnContactRemoved(const SubShapeIDPair& inSubShapePair) override
    {
        std::cout << "A contact was removed" << std::endl;
    }
};

// An example activation listener
class MyBodyActivationListener : public BodyActivationListener
{
public:
    virtual void OnBodyActivated(const BodyID& inBodyID, uint64 inBodyUserData) override
    {
        std::cout << "A body got activated" << std::endl;
    }

    virtual void OnBodyDeactivated(const BodyID& inBodyID, uint64 inBodyUserData) override
    {
        std::cout << "A body went to sleep" << std::endl;
    }
};
