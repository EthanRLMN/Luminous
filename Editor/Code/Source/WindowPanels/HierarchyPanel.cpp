#include "WindowPanels/HierarchyPanel.hpp"
#include "Editor.hpp"
#include "Game/Systems/Entity/Entity.hpp"
#include "Game/Systems/Entity/EntityManager.hpp"
#include "imgui.h"

void HierarchyPanel::Render()
{
    IWindowPanel::Render();

    if (!p_isOpen)
        return;

    ImGui::Begin(p_windowIdentifier.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);

    m_rootEntities.clear();
    BuildHierarchy();

    for (const auto& root : m_rootEntities)
    {
        DrawEntityNode(root);
    }

    ImGui::End();
}

void HierarchyPanel::BuildHierarchy()
{
    const std::vector<std::shared_ptr<Entity>> allEntities = p_editor->GetEngine()->GetEntityManager()->GetEntities();

    std::unordered_map<Entity*, EntityNode> entityNodeMap;

    for (const auto& entity : allEntities)
    {
        entityNodeMap[entity.get()] = EntityNode(entity);
    }

    for (const auto& entity : allEntities)
    {
        const auto& parent = entity->GetParent();

        if (parent)
        {
            entityNodeMap[parent.get()].children.push_back(entityNodeMap[entity.get()]);
        } else
        {
            m_rootEntities.push_back(entityNodeMap[entity.get()]);
        }
    }
}

void HierarchyPanel::DrawEntityNode(const EntityNode& node)
{
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;

    if (node.children.empty())
        flags |= ImGuiTreeNodeFlags_Leaf;

    bool open = ImGui::TreeNodeEx(node.entity->GetName().c_str(), flags);

    if (open)
    {
        for (const auto& child : node.children)
        {
            DrawEntityNode(child);
        }
        ImGui::TreePop();
    }
}
