#include "Game/Scene.hpp"

#include "Game/Systems/Entity/EntityFactory.hpp"
#include "Game/Systems/Entity/EntityTemplates.hpp"

void Scene::RegisterScene(EntityManager& a_entityManager)
{
    EntityTemplates l_defaultTemplates {};
    l_defaultTemplates.RegisterEntityTemplates();

    a_entityManager.CreateEntityFromTemplate("Cube");
    //a_entityManager.CreateEntityFromTemplate("Sphere");
    //a_entityManager.CreateEntityFromTemplate("Empty");
}
