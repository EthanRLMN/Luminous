#pragma once

#include <memory> // Pour les shared_ptr
#include "Game/Scene.hpp"
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

        EntityNode() :
            entity(nullptr), children() {}

        EntityNode(std::shared_ptr<Entity> entity) :
            entity(entity), children() {}
    };

    std::vector<EntityNode> m_rootEntities;

    void BuildHierarchy();
    void DrawEntityNode(const EntityNode& node);
};
