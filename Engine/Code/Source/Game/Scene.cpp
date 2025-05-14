#include "Game/Scene.hpp"

#include "Game/Systems/Entity/EntityFactory.hpp"
#include "Game/Systems/Entity/EntityTemplates.hpp"

#include "Game/Systems/Component/RigidbodyComponent.hpp"

void Scene::RegisterScene(EntityManager& a_entityManager)
{
    EntityTemplates l_defaultTemplates {};
    l_defaultTemplates.RegisterEntityTemplates();

    a_entityManager.CreateEntityFromTemplate("Cube");
    //a_entityManager.CreateEntityFromTemplate("Sphere");
    a_entityManager.CreateEntityFromTemplate("Empty");
    a_entityManager.CreateEntityFromTemplate("Empty");

    Engine* engine = a_entityManager.GetEngine();

    
    a_entityManager.GetEntities()[1].get()->AddComponent(std::make_shared<RigidbodyComponent>());
    a_entityManager.GetEntities()[1].get()->GetComponent<RigidbodyComponent>().get()->SetEngine(engine);
    a_entityManager.GetEntities()[1].get()->GetComponent<RigidbodyComponent>().get()->SetEntity(a_entityManager.GetEntities()[1]);
    a_entityManager.GetEntities()[1].get()->GetComponent<TransformComponent>().get()->SetLocalPosition(Maths::Vector3(5.f,15.0f,0.0f));
    a_entityManager.GetEntities()[1].get()->GetComponent<RigidbodyComponent>().get()->SetLayer(Layers::DYNAMIC);
    a_entityManager.GetEntities()[1].get()->GetComponent<RigidbodyComponent>().get()->m_active = JPH::EActivation::Activate;
    a_entityManager.GetEntities()[1].get()->GetComponent<RigidbodyComponent>().get()->Initialize();

    a_entityManager.GetEntities()[2].get()->GetComponent<TransformComponent>().get()->SetLocalScale(Maths::Vector3(1.f, 3.f, 1.f));
    a_entityManager.GetEntities()[2].get()->AddComponent(std::make_shared<RigidbodyComponent>());
    a_entityManager.GetEntities()[2].get()->GetComponent<RigidbodyComponent>().get()->SetEngine(engine);
    a_entityManager.GetEntities()[2].get()->GetComponent<RigidbodyComponent>().get()->SetEntity(a_entityManager.GetEntities()[2]);
    a_entityManager.GetEntities()[2].get()->GetComponent<TransformComponent>().get()->SetLocalPosition(Maths::Vector3(5.15f, -10.0f, 0.f));
    a_entityManager.GetEntities()[2].get()->GetComponent<RigidbodyComponent>().get()->SetLayer(Layers::STATIC);
    a_entityManager.GetEntities()[2].get()->GetComponent<RigidbodyComponent>().get()->m_active = JPH::EActivation::DontActivate;
    a_entityManager.GetEntities()[2].get()->GetComponent<RigidbodyComponent>().get()->Initialize();

}
