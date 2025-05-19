#include "Game/Systems/Entity/EntityTemplates.hpp"

#include "Game/Systems/Component/MeshRendererComponent.hpp"
#include "Game/Systems/Component/ModelComponent.hpp"
#include "Game/Systems/Component/RigidbodyComponent.hpp"
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
    Skybox();
}


void EntityTemplates::DefaultEmpty()
{
    EntityFactory::Get().RegisterEntity("DefaultEmpty", [](EntityManager& a_entityManager)
    {
        auto l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("DefaultEmpty");

        
        const std::shared_ptr<TransformComponent> l_transform = std::make_shared<TransformComponent>();
        l_entity->AddComponent(l_transform);
        l_transform->SetOwner(l_entity);




        return l_entity;
    });
}


void EntityTemplates::DefaultCube()
{
    EntityFactory::Get().RegisterEntity("DefaultCube", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("DefaultCube");

        const std::shared_ptr<TransformComponent> l_transform = std::make_shared<TransformComponent>();
        l_entity->AddComponent(l_transform);
        l_transform->SetOwner(l_entity);

        const std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Cube.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/White.png");
        l_entity->AddComponent(l_modelComponent);

        const std::shared_ptr<MeshRendererComponent> l_meshRendererComponent = std::make_shared<MeshRendererComponent>();
        l_entity->AddComponent(l_meshRendererComponent);

        

        return l_entity;
    });
}


void EntityTemplates::DefaultSphere()
{
    EntityFactory::Get().RegisterEntity("DefaultSphere", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("DefaultSphere");

        const std::shared_ptr<TransformComponent> l_transform = std::make_shared<TransformComponent>();
        l_entity->AddComponent(l_transform);
        l_transform->SetOwner(l_entity);

        const std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Sphere.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/White.png");
        l_entity->AddComponent(l_modelComponent);

        const std::shared_ptr<MeshRendererComponent> l_meshRendererComponent = std::make_shared<MeshRendererComponent>();
        l_entity->AddComponent(l_meshRendererComponent);

        return l_entity;
    });
}


void EntityTemplates::DefaultCapsule()
{
    EntityFactory::Get().RegisterEntity("DefaultCapsule", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("DefaultCapsule");

        const std::shared_ptr<TransformComponent> l_transform = std::make_shared<TransformComponent>();
        l_entity->AddComponent(l_transform);
        l_transform->SetOwner(l_entity);

        const std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Capsule.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/White.png");
        l_entity->AddComponent(l_modelComponent);

        const std::shared_ptr<MeshRendererComponent> l_meshRendererComponent = std::make_shared<MeshRendererComponent>();
        l_entity->AddComponent(l_meshRendererComponent);

        return l_entity;
    });
}


void EntityTemplates::DefaultCylinder()
{
    EntityFactory::Get().RegisterEntity("DefaultCylinder", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("DefaultCylinder");

        const std::shared_ptr<TransformComponent> l_transform = std::make_shared<TransformComponent>();
        l_entity->AddComponent(l_transform);
        l_transform->SetOwner(l_entity);

        const std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Cylinder.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/White.png");
        l_entity->AddComponent(l_modelComponent);

        const std::shared_ptr<MeshRendererComponent> l_meshRendererComponent = std::make_shared<MeshRendererComponent>();
        l_entity->AddComponent(l_meshRendererComponent);

        return l_entity;
    });
}


void EntityTemplates::DefaultCone()
{
    EntityFactory::Get().RegisterEntity("DefaultCone", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("DefaultCone");

        const std::shared_ptr<TransformComponent> l_transform = std::make_shared<TransformComponent>();
        l_entity->AddComponent(l_transform);
        l_transform->SetOwner(l_entity);

        const std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Cone.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/White.png");
        l_entity->AddComponent(l_modelComponent);

        const std::shared_ptr<MeshRendererComponent> l_meshRendererComponent = std::make_shared<MeshRendererComponent>();
        l_entity->AddComponent(l_meshRendererComponent);

        return l_entity;
    });
}


void EntityTemplates::DefaultMonkey()
{
    EntityFactory::Get().RegisterEntity("DefaultMonkey", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("DefaultMonkey");

        const std::shared_ptr<TransformComponent> l_transform = std::make_shared<TransformComponent>();
        l_entity->AddComponent(l_transform);
        l_transform->SetOwner(l_entity);

        const std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Monkey.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/White.png");
        l_entity->AddComponent(l_modelComponent);

        const std::shared_ptr<MeshRendererComponent> l_meshRendererComponent = std::make_shared<MeshRendererComponent>();
        l_entity->AddComponent(l_meshRendererComponent);

        return l_entity;
    });
}


void EntityTemplates::DefaultCompanion()
{
    EntityFactory::Get().RegisterEntity("DefaultCompanion", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("DefaultCompanion");

        const std::shared_ptr<TransformComponent> l_transform = std::make_shared<TransformComponent>();
        l_entity->AddComponent(l_transform);
        l_transform->SetOwner(l_entity);

        const std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/CompanionCube.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/CompanionCube.png");
        l_entity->AddComponent(l_modelComponent);

        const std::shared_ptr<MeshRendererComponent> l_meshRendererComponent = std::make_shared<MeshRendererComponent>();
        l_entity->AddComponent(l_meshRendererComponent);

        return l_entity;
    });
}


void EntityTemplates::DefaultPlane()
{
    EntityFactory::Get().RegisterEntity("DefaultPlane", [](EntityManager& a_entityManager)
    {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("DefaultPlane");

        const std::shared_ptr<TransformComponent> l_transform = std::make_shared<TransformComponent>();
        l_entity->AddComponent(l_transform);
        l_transform->SetOwner(l_entity);

        const std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/Plane.fbx");
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/White.png");
        l_entity->AddComponent(l_modelComponent);

        const std::shared_ptr<MeshRendererComponent> l_meshRendererComponent = std::make_shared<MeshRendererComponent>();
        l_entity->AddComponent(l_meshRendererComponent);

        return l_entity;
    });
}


void EntityTemplates::Skybox()
{
    EntityFactory::Get().RegisterEntity("Skybox", [](EntityManager& a_entityManager)
                                        {
        std::shared_ptr<Entity> l_entity = std::make_shared<Entity>(a_entityManager);
        l_entity->SetName("Skybox");


        const std::shared_ptr<TransformComponent> l_transform = std::make_shared<TransformComponent>();
        l_entity->AddComponent(l_transform);
        l_transform->SetOwner(l_entity);

        l_transform->SetLocalPosition(Maths::Vector3(0,0,0));
        l_transform->SetLocalRotationVec(Maths::Vector3(-90, 0, 180));
        l_transform->SetLocalScale(Maths::Vector3(-90, -90, -90));
       

   
        const std::shared_ptr<ModelComponent> l_modelComponent = std::make_shared<ModelComponent>();
        l_modelComponent->SetMeshPath("Engine/Assets/Default/Models/SphereInverse.fbx");  
        l_modelComponent->SetTexturePath("Engine/Assets/Default/Textures/sky_water_landscape.jpg");
        
        l_entity->AddComponent(l_modelComponent);

  
        const std::shared_ptr<MeshRendererComponent> l_meshRendererComponent = std::make_shared<MeshRendererComponent>();
        l_entity->AddComponent(l_meshRendererComponent);

        return l_entity; });
}
