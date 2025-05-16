#include "Game/Systems/Component/MeshRendererComponent.hpp"
#include "Game/Systems/Entity/EntityManager.hpp"
#include "Game/Systems/Entity/EntityFactory.hpp"


void EntityManager::Initialize(Engine* a_engine)
{
    m_engine = a_engine;
    for (const std::shared_ptr<Entity>& l_entity : m_entities)
    {
        l_entity->SetEngine(a_engine);
        l_entity->Initialize();
    }
}


void EntityManager::Update() const
{
    for (const std::shared_ptr<Entity>& l_entity : m_entities)
        l_entity->Update();
}


std::shared_ptr<Entity> EntityManager::GetFirstEntityByParent(const std::shared_ptr<Entity>& a_parent) const
{
    for (const std::shared_ptr<Entity>& l_entity : m_entities)
    {
        if (l_entity->Transform()->GetParent() == a_parent)
            return l_entity;
    }
    return nullptr;
}


std::shared_ptr<Entity> EntityManager::CreateEntityFromTemplate(const std::string& a_templateName)
{
    std::shared_ptr<Entity> l_entity = EntityFactory::Get().CreateEntity(a_templateName, *this);

    if (l_entity)
    {
        m_entities.push_back(l_entity);

        if (m_engine)
        {
            l_entity->SetEngine(m_engine);
            l_entity->Initialize();
        }
    }
    return l_entity;
}


void EntityManager::GameplayStarted() const
{
    for (const std::shared_ptr<Entity>& l_entity : m_entities)
        l_entity->GameplayStarted();
}


std::vector<std::string> EntityManager::GetAvailableTemplates()
{
    return EntityFactory::Get().GetAvailableTemplates();
}


std::shared_ptr<Entity> EntityManager::GetEntityByName(const std::string& a_name) const
{
    for (const std::shared_ptr<Entity>& l_entity : m_entities)
    {
        if (l_entity->GetName() == a_name)
            return l_entity;
    }
    return nullptr;
}