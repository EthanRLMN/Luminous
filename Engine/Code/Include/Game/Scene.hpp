#pragma once

#include "EntitySystem/Entity.hpp"

class Engine;

class Scene
{
public:
    Scene()= default;
    ~Scene()= default;

    void SceneEntity(EntityManager& a_entityManager,Engine* a_engine);
};

