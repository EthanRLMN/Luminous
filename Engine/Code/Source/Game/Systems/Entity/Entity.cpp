#include "Game/Systems/Entity/Entity.hpp"
#include "Game/Systems/Component/TransformComponent.hpp"


void Entity::AddComponent(const std::shared_ptr<EntityComponent>& a_component)
{
    a_component->SetOwner(shared_from_this());
    m_components.push_back(a_component);
}


void Entity::SetActive(const bool a_isActive)
{
    m_isActive = a_isActive;
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