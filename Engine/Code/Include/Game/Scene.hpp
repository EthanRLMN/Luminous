#pragma once

#include "Systems/Entity/Entity.hpp"

class Engine;

class Scene
{
public:
    Scene()= default;
    ~Scene()= default;

    void RegisterScene(EntityManager& a_entityManager);
};

