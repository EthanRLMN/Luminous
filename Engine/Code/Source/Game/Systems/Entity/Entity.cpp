#include "Game/Systems/Entity/Entity.hpp"

#include "Engine.hpp"
#include "Game/Systems/Time.inl"
#include "Game/Systems/Component/LightComponent.hpp"
#include "Game/Systems/Component/MeshRendererComponent.hpp"
#include "Game/Systems/Component/TransformComponent.hpp"
#include "Game/Systems/Entity/EntityManager.hpp"


void Entity::AddComponent(const std::shared_ptr<EntityComponent>& a_component)
{
    a_component->SetOwner(shared_from_this());
    m_components.push_back(a_component);

    if (a_component == std::dynamic_pointer_cast<MeshRendererComponent>(a_component))
        m_entityManager.RegisterRenderable(shared_from_this());

    if (a_component == std::dynamic_pointer_cast<LightComponent>(a_component))
        m_entityManager.RegisterLight(shared_from_this());
}


void Entity::RemoveComponent(const std::shared_ptr<EntityComponent>& a_component)
{
    a_component->SetOwner(nullptr);
    m_components.erase(std::ranges::find(m_components, a_component));

    if (a_component == std::dynamic_pointer_cast<MeshRendererComponent>(a_component))
        m_entityManager.UnregisterRenderable(shared_from_this());

    if (a_component == std::dynamic_pointer_cast<LightComponent>(a_component))
        m_entityManager.UnregisterLight(shared_from_this());
}


void Entity::RemoveAllComponents()
{
    for (const std::shared_ptr<EntityComponent>& l_component : m_components)
        RemoveComponent(l_component);
}


void Entity::Initialize() const
{
    for (const std::shared_ptr<EntityComponent>& l_component : m_components)
    {
        l_component->SetEngine(m_engine);
        l_component->Initialize();
    }

    for (const std::shared_ptr<TransformComponent>& l_child : Transform()->GetChildren())
    {
        l_child->GetOwner()->SetEngine(m_engine);
        l_child->GetOwner()->Initialize();
    }
}


void Entity::GameplayStarted() const
{
    for (const std::shared_ptr<EntityComponent>& l_component : m_components)
        l_component->GameplayStarted();

    for (const std::shared_ptr<TransformComponent>& l_child : Transform()->GetChildren())
        l_child->GetOwner()->GameplayStarted();
}


void Entity::Update() const
{
    for (const std::shared_ptr<EntityComponent>& l_component : m_components)
        l_component->Update();

    for (const std::shared_ptr<TransformComponent>& l_child : Transform()->GetChildren())
        l_child->GetOwner()->Update();
}
