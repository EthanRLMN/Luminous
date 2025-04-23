#pragma once
#include "EntitySystem/Entity.hpp"

class Scene
{
public:
    Scene(){};
    ~Scene(){};

    void SceneEntity();
private:
    EntityManager entityManager;

};

