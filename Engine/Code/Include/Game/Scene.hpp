#pragma once

#include "Systems/Entity/Entity.hpp"

#include <iostream>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <string>
#include <vector>

class Engine;

struct Entity_Saver
{
    rfl::Rename<"name", std::string> entityName;
    uint16_t entityUUID;
    bool isActive;
};

class Scene
{
public:
    Scene()= default;
    ~Scene()= default;

    void RegisterScene(EntityManager& a_entityManager);
};

