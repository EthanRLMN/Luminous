#include <iostream>
#include <cstdarg>
#include <thread>


#include "Struct/Vertex.hpp"

#include "jolt/Jolt/Jolt.h"


#include <Jolt/Physics/Collision/ObjectLayer.h>
#include "Jolt/Renderer/DebugRenderer.h"
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
