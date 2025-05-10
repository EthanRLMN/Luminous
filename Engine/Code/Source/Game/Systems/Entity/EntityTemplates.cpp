#include "Game/Systems/Entity/EntityTemplates.hpp"

#include "Game/Systems/Entity/EntityFactory.hpp"


void EntityTemplates::RegisterEntityTemplates()
{
    RegisterEmptyEntityTemplate();
    RegisterCubeEntityTemplate();
    RegisterPlaneEntityTemplate();
    RegisterSphereEntityTemplate();
}


void EntityTemplates::RegisterEmptyEntityTemplate()
{
    EntityFactory::Get().RegisterEntity("Empty", [](EntityManager& a_entityManager)
    {
        auto l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("Empty");
        return l_entity;
    });
}


void EntityTemplates::RegisterCubeEntityTemplate()
{
    EntityFactory::Get().RegisterEntity("Cube", [](EntityManager& a_entityManager)
    {
        auto l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("Cube");
        return l_entity;
    });
}


void EntityTemplates::RegisterPlaneEntityTemplate()
{
    EntityFactory::Get().RegisterEntity("Plane", [](EntityManager& a_entityManager)
    {
        auto l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("Plane");
        return l_entity;
    });
}


void EntityTemplates::RegisterSphereEntityTemplate()
{
    EntityFactory::Get().RegisterEntity("Sphere", [](EntityManager& a_entityManager)
    {
        auto l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("Sphere");
        return l_entity;
    });
}
