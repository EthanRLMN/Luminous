#include "Game/Systems/Entity/EntityTemplates.hpp"
#include "Game/Systems/Component/ModelComponent.hpp"
#include "Game/Systems/Entity/EntityFactory.hpp"


void EntityTemplates::RegisterEntityTemplates()
{
    Empty();
    Cube();
    Plane();
    Sphere();
    Cone();
    Cylinder();
    Capsule();
    Monkey();
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
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Cube.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/default.png");
        l_entity->AddComponent(l_modelComponent);

        return l_entity;
    });
}

void EntityTemplates::Plane()
{
    EntityFactory::Get().RegisterEntity("Plane", [](EntityManager& a_entityManager)
                                        {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("Plane");
        std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Plane.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/default.png");
        l_entity->AddComponent(l_modelComponent);
        return l_entity; });
}

void EntityTemplates::Sphere()
{
    EntityFactory::Get().RegisterEntity("Sphere", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("Sphere");

        std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Sphere.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/default.png");
        l_entity->AddComponent(l_modelComponent);

        return l_entity;
    });
}

void EntityTemplates::Cone()
{
    EntityFactory::Get().RegisterEntity("Cone", [](EntityManager& a_entityManager)
                                        {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("Cone");
        std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Cone.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/default.png");
        l_entity->AddComponent(l_modelComponent);
        return l_entity; });
}

void EntityTemplates::Cylinder()
{
    EntityFactory::Get().RegisterEntity("Cylinder", [](EntityManager& a_entityManager)
                                        {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("Cylinder");
        std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Cylinder.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/default.png");
        l_entity->AddComponent(l_modelComponent);
        return l_entity; });
}

void EntityTemplates::Capsule()
{
    EntityFactory::Get().RegisterEntity("Capsule", [](EntityManager& a_entityManager)
                                        {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("Capsule");
        std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Capsule.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/default.png");
        l_entity->AddComponent(l_modelComponent);
        return l_entity; });
}

void EntityTemplates::Monkey()
{
    EntityFactory::Get().RegisterEntity("Monkey", [](EntityManager& a_entityManager)
                                        {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("Monkey");
        std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Monkey.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/default.png");
        l_entity->AddComponent(l_modelComponent);
        return l_entity; });
}


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