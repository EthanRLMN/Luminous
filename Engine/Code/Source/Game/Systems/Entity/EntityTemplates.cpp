#include "Game/Systems/Entity/EntityTemplates.hpp"
#include "Game/Systems/Component/ModelComponent.hpp"
#include "Game/Systems/Entity/EntityFactory.hpp"


void EntityTemplates::RegisterEntityTemplates()
{
    DefaultEmpty();
    DefaultCube();
    DefaultPlane();
    DefaultSphere();
    DefaultCompanion();
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

        std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Cube.obj");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/Cube.png");
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

        std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/VikingRoom.obj");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/VikingRoom.png");
        l_entity->AddComponent(l_modelComponent);

        return l_entity;
    });
}


void EntityTemplates::Capsule()
{

}


void EntityTemplates::Cylinder()
{

}


void EntityTemplates::Cone()
{

}


void EntityTemplates::Monkey()
{

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
        auto l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("DefaultPlane");
        return l_entity;
    });
}
