#pragma once
#include <unordered_set>

#include "Game/Scene.hpp"
#include "Game/Systems/Entity/Entity.hpp"
#include "Game/Systems/Entity/EntityManager.hpp"
#include "Interface/IWindowPanel.hpp"

class HierarchyPanel : public IWindowPanel
{
public:
    explicit HierarchyPanel(Editor* a_editor, const std::string& a_windowIdentifier) :
        IWindowPanel(a_editor, a_windowIdentifier) {}

    void Init() override {};
    void Update() override {};
    void Render() override;
    void Destroy() override {};

private:
    struct EntityNode
    {
        std::shared_ptr<Entity> entity;
        std::vector<EntityNode> children;

        EntityNode() = default;
        EntityNode(std::shared_ptr<Entity> entity) : entity(std::move(entity)) {}
    };

    std::vector<EntityNode> m_rootEntities;

    bool m_isCreatingEntity = false;
    char m_newEntityName[256] = "New Entity";

    void BuildHierarchy();
    void DrawEntityNode(const EntityNode& node);
    bool IsDescendant(const std::shared_ptr<Entity>& child, const std::shared_ptr<Entity>& parent) const;
    std::string GenerateUniqueEntityName(const std::string& baseName);
};
