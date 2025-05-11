#include "Game/Systems/Entity/Entity.hpp"

#include "Game/Systems/Component/ModelComponent.hpp"

std::vector<std::shared_ptr<Entity>> Entity::GetEntitiesWithModelComponent() const
{
    std::vector<std::shared_ptr<Entity>> l_entitiesWithModel;
    for (const std::shared_ptr<Entity>& entity : m_entities)
    {
        std::shared_ptr<ModelComponent> modelComponent = entity->GetComponent<ModelComponent>();
        if (modelComponent != nullptr)
            l_entitiesWithModel.push_back(entity);
    }
    return l_entitiesWithModel;
}

void Entity::Initialize() const
{
    for (const std::shared_ptr<EntityComponent>& l_component : m_components)
    {
        l_component->SetEngine(m_engine);
        l_component->Initialize();
    }

    for (const std::shared_ptr<Entity>& l_child : m_children)
    {
        l_child->SetEngine(m_engine);
        l_child->Initialize();
    }
}

void Entity::GameplayStarted() const
{
    for (const std::shared_ptr<EntityComponent>& l_component : m_components)
        l_component->GameplayStarted();

    for (const std::shared_ptr<Entity>& l_child : m_children)
        l_child->GameplayStarted();
}

void Entity::Update() const
{
    for (const std::shared_ptr<EntityComponent>& l_component : m_components)
        l_component->Update();

    for (const std::shared_ptr<Entity>& l_child : m_children)
        l_child->Update();
}
