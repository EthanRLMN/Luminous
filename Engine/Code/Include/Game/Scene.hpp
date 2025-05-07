#pragma once

#include "EntitySystem/Entity.hpp"
#include "ResourceManager/ResourceManager.hpp"


class Scene
{
public:
    Scene()= default;
    ~Scene()= default;

    void SceneEntity(EntityManager& a_entityManager, IResourceManager* a_resourceManager);

private:
    IResourceManager* m_manager;
      
};

