#include "Game/Systems/Entity/EntityTemplates.hpp"
#include "Game/Systems/Component/ModelComponent.hpp"
#include "Game/Systems/Entity/EntityFactory.hpp"


void EntityTemplates::RegisterEntityTemplates()
{
    Empty();
    Cube();
    Plane();
    Sphere();
    Companion();
}


void EntityTemplates::Empty()
{
    EntityFactory::Get().RegisterEntity("Empty", [](EntityManager& a_entityManager)
    {
        auto l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("Empty");
        return l_entity;
    });
}


void EntityTemplates::Cube()
{
    EntityFactory::Get().RegisterEntity("Cube", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("Cube");

        std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/CubeUE.FBX");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/DefaultTexture.png");
        l_entity->AddComponent(l_modelComponent);

        return l_entity;
    });
}


void EntityTemplates::Sphere()
{
    EntityFactory::Get().RegisterEntity("Sphere", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("Sphere");

        std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/VikingRoom.obj");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/VikingRoom.png");
        l_entity->AddComponent(l_modelComponent);

        return l_entity;
    });
}


void EntityTemplates::Capsule() {}


void EntityTemplates::Cylinder() {}


void EntityTemplates::Cone() {}


void EntityTemplates::Monkey() {}


void EntityTemplates::Companion()
{
    EntityFactory::Get().RegisterEntity("Companion", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("Companion");

        std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/CompanionCube.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/CompanionCube.png");
        l_entity->AddComponent(l_modelComponent);

        return l_entity;
    });
}


void EntityTemplates::Plane()
{
    EntityFactory::Get().RegisterEntity("Plane", [](EntityManager& a_entityManager)
    {
        auto l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("Plane");
        return l_entity;
    });
}
