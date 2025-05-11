#include "Game/Systems/Entity/EntityTemplates.hpp"
#include "Game/Systems/Component/ModelComponent.hpp"
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
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("Cube");

        std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_entity->AddComponent(l_modelComponent);

        return l_entity;
    });
}


void EntityTemplates::RegisterSphereEntityTemplate()
{
    EntityFactory::Get().RegisterEntity("Sphere", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("Sphere");

        std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        //l_modelComponent->SetMesh("Engine/Assets/Default/Models/viking_room.obj");
        //l_modelComponent->SetTexture("Engine/Assets/Default/Textures/viking_room.png");
        l_entity->AddComponent(l_modelComponent);

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