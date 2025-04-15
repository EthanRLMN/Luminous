
#include "Logger.hpp"
#include <iostream>
#include <cstdarg>
#include <thread>


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
    Physics();

    ~Physics() {};

    void Init_JOLT();
    void Update_JOLT();
    void Clean_JOLT();

    JPH::Body* CreateBody();
   
    
    
private:


    float cDeltaTime{ 0.f };
    uint step{ 0 };
    PhysicsSystem* physics_system { };
    const BodyInterface& body_interface { };
    BodyID* sphere_id{ 0 };
    

    TempAllocatorImpl* temp_allocator{nullptr};
    JobSystemThreadPool* job_system{nullptr};
   
};


