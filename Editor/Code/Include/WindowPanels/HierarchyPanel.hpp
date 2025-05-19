#pragma once
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "Game/Scene.hpp"
#include "Game/Systems/Entity/Entity.hpp"
#include "Game/Systems/Entity/EntityManager.hpp"
#include "InspectorPanel.hpp"
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

    void SetInspectorPanel(InspectorPanel* inspector) { m_inspectorPanel = inspector; }

private:
    struct EntityNode
    {
        std::shared_ptr<Entity> entity;
        std::vector<std::shared_ptr<EntityNode>> children;

        EntityNode() = default;
        EntityNode(std::shared_ptr<Entity> entity) :
            entity(std::move(entity)) {}
    };

    std::vector<std::shared_ptr<EntityNode>> m_rootEntities;
    InspectorPanel* m_inspectorPanel = nullptr;

    std::shared_ptr<Entity> m_entityToReparent = nullptr;
    std::shared_ptr<Entity> m_newParent = nullptr;

    bool m_isCreatingEntity = false;
    char m_newEntityName[256] = "New Entity";

    std::shared_ptr<Entity> m_entityToRename = nullptr;
    std::shared_ptr<Entity> m_entityToDelete = nullptr;
    char m_renameBuffer[128] = {};
    bool m_showRenamePopup = false;
    std::vector<std::shared_ptr<Entity>> m_pendingDeletes;

    void BuildHierarchy();
    void DrawEntityNode(const std::shared_ptr<EntityNode>& node);
    bool IsDescendant(const std::shared_ptr<Entity>& child, const std::shared_ptr<Entity>& parent) const;
    std::string GenerateUniqueEntityName(const std::string& baseName);
};
