#include "Game/Scene.hpp"

#include "Game/Systems/Entity/EntityFactory.hpp"
#include "Game/Systems/Entity/EntityTemplates.hpp"

void Scene::RegisterScene(EntityManager& a_entityManager)
{
    EntityTemplates l_defaultTemplates{};
    l_defaultTemplates.RegisterEntityTemplates();

    auto l_cube = a_entityManager.CreateEntityFromTemplate("Cube");
    auto getglobal = l_cube->GetComponent<TransformComponent>()->GetGlobalPosition();
}
