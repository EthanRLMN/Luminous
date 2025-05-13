#include "Game/Systems/Entity/EntityTemplates.hpp"
#include "Game/Systems/Component/ModelComponent.hpp"
#include "Game/Systems/Entity/EntityFactory.hpp"


void EntityTemplates::RegisterEntityTemplates()
{
    DefaultEmpty();
    DefaultCube();
    DefaultSphere();
    DefaultCapsule();
    DefaultCylinder();
    DefaultCone();
    DefaultMonkey();
    DefaultCompanion();
    DefaultPlane();
}


void EntityTemplates::DefaultEmpty()
{
    EntityFactory::Get().RegisterEntity("DefaultEmpty", [](EntityManager& a_entityManager)
    {
        auto l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("DefaultEmpty");
        return l_entity;
    });
}


void EntityTemplates::DefaultCube()
{
    EntityFactory::Get().RegisterEntity("DefaultCube", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("DefaultCube");

        const std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Cube.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/White.png");
        l_entity->AddComponent(l_modelComponent);

        return l_entity;
    });
}


void EntityTemplates::DefaultSphere()
{
    EntityFactory::Get().RegisterEntity("DefaultSphere", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("DefaultSphere");

        const std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Sphere.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/White.png");
        l_entity->AddComponent(l_modelComponent);

        return l_entity;
    });
}


void EntityTemplates::DefaultCapsule()
{
    EntityFactory::Get().RegisterEntity("DefaultCapsule", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("DefaultCapsule");

        const std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Capsule.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/White.png");
        l_entity->AddComponent(l_modelComponent);

        return l_entity;
    });
}


void EntityTemplates::DefaultCylinder()
{
    EntityFactory::Get().RegisterEntity("DefaultCylinder", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("DefaultCylinder");

        const std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Cylinder.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/White.png");
        l_entity->AddComponent(l_modelComponent);

        return l_entity;
    });
}


void EntityTemplates::DefaultCone()
{
    EntityFactory::Get().RegisterEntity("DefaultCone", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("DefaultCone");

        const std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Cone.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/White.png");
        l_entity->AddComponent(l_modelComponent);

        return l_entity;
    });
}


void EntityTemplates::DefaultMonkey()
{
    EntityFactory::Get().RegisterEntity("DefaultMonkey", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("DefaultMonkey");

        const std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Monkey.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/White.png");
        l_entity->AddComponent(l_modelComponent);

        return l_entity;
    });
}


void EntityTemplates::DefaultCompanion()
{
    EntityFactory::Get().RegisterEntity("DefaultCompanion", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("DefaultCompanion");

        std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/CompanionCube.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/CompanionCube.png");
        l_entity->AddComponent(l_modelComponent);

        return l_entity;
    });
}


void EntityTemplates::DefaultPlane()
{
    EntityFactory::Get().RegisterEntity("DefaultPlane", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("DefaultPlane");

        std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Plane.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/White.png");
        l_entity->AddComponent(l_modelComponent);

        return l_entity;
    });
}
