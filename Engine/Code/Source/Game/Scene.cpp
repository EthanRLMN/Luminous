#include "Game/Scene.hpp"

#include "Game/Systems/Time.inl"
#include "Game/Systems/Entity/EntityFactory.hpp"
#include "Game/Systems/Entity/EntityTemplates.hpp"

void Scene::RegisterScene(EntityManager& a_entityManager)
{
    EntityTemplates l_defaultTemplates {};
    l_defaultTemplates.RegisterEntityTemplates();

    auto l_cube = a_entityManager.CreateEntityFromTemplate("Cube");
    auto l_sphere = a_entityManager.CreateEntityFromTemplate("Sphere");
    l_sphere->Transform()->SetLocalPosition(Maths::Vector3::One);
    l_sphere->Transform()->SetParent(l_cube);

    for (const auto& l_entity : EntityManager::GetAvailableTemplates())
    {
        DEBUG_LOG_CRITICAL("{}", l_entity);
    }
}
