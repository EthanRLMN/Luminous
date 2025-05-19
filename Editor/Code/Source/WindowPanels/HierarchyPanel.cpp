#include "WindowPanels/HierarchyPanel.hpp"

#include <iostream>

void HierarchyPanel::Render()
{
    IWindowPanel::Render();

    if (!p_isOpen)
        return;

    ImGui::Begin(p_windowIdentifier.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);

    m_rootEntities.clear();

    static char newEntityName[128] = "New Entity";

    if (ImGui::BeginPopupContextWindow("HierarchyContextMenu", ImGuiPopupFlags_MouseButtonRight))
    {
        if (ImGui::BeginMenu("Add new Entity..."))
        {
            auto createEntity = [&](const std::string& templateName)
            {
                ImGui::OpenPopup("CreateEntityPopup");
                p_editor->GetEngine()->GetEntityManager()->CreateEntityFromTemplate(templateName);
            };

            if (ImGui::MenuItem("Empty"))
                createEntity("DefaultEmpty");
            if (ImGui::MenuItem("Cube"))
                createEntity("DefaultCube");
            if (ImGui::MenuItem("Plane"))
                createEntity("DefaultPlane");
            if (ImGui::MenuItem("Sphere"))
                createEntity("DefaultSphere");
            if (ImGui::MenuItem("Cone"))
                createEntity("DefaultCone");
            if (ImGui::MenuItem("Cylinder"))
                createEntity("DefaultCylinder");
            if (ImGui::MenuItem("Capsule"))
                createEntity("DefaultCapsule");
            if (ImGui::MenuItem("Monkey"))
                createEntity("DefaultMonkey");
            if (ImGui::MenuItem("Companion"))
                createEntity("DefaultCompanion");

            ImGui::EndMenu();
        }
        ImGui::EndPopup();
    }

    if (ImGui::BeginPopupModal("CreateEntityPopup", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::InputText("Entity name", newEntityName, IM_ARRAYSIZE(newEntityName));

        if (ImGui::Button("Create"))
        {
            auto entityManager = p_editor->GetEngine()->GetEntityManager();
            auto newEntity = entityManager->CreateEntityFromTemplate("DefaultCompanion");
            newEntity->SetName(GenerateUniqueEntityName(newEntityName));

            std::memset(newEntityName, 0, sizeof(newEntityName));
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            std::memset(newEntityName, 0, sizeof(newEntityName));
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    BuildHierarchy();

    for (const auto& root : m_rootEntities)
        DrawEntityNode(root);

    if (m_entityToReparent)
    {
        m_entityToReparent->Transform()->SetParent(m_newParent);
        BuildHierarchy();
        m_entityToReparent = nullptr;
        m_newParent = nullptr;
    }

    ImVec2 avail = ImGui::GetContentRegionAvail();

    if (avail.x > 0.0f && avail.y > 0.0f)
    {
        ImGui::InvisibleButton("##DetachZone", avail);

        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ENTITY_DRAG"))
            {
                Entity* droppedRawPtr = *(Entity**) payload->Data;
                m_entityToReparent = p_editor->GetEngine()->GetEntityManager()->GetEntityByRawPointer(droppedRawPtr);
                m_newParent = nullptr;
            }
            ImGui::EndDragDropTarget();
        }
    }

    if (m_showRenamePopup && m_entityToRename)
    {
        ImGui::OpenPopup("RenameEntityPopup");
        m_showRenamePopup = false;
    }

    if (ImGui::BeginPopupModal("RenameEntityPopup", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::InputText("New name", m_renameBuffer, IM_ARRAYSIZE(m_renameBuffer));

        if (ImGui::Button("OK"))
        {
            m_entityToRename->SetName(GenerateUniqueEntityName(m_renameBuffer));
            m_entityToRename = nullptr;
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            m_entityToRename = nullptr;
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    if (!m_pendingDeletes.empty())
    {
        auto entityManager = p_editor->GetEngine()->GetEntityManager();
        for (const auto& e : m_pendingDeletes)
        {
            entityManager->RemoveEntity(e);
        }
        m_pendingDeletes.clear();
        BuildHierarchy();
    }

    ImGui::End();
}


void HierarchyPanel::DrawEntityNode(const std::shared_ptr<EntityNode>& node)
{
    if (!node || !node->entity)
        return;

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

    if (node->children.empty())
        flags |= ImGuiTreeNodeFlags_Leaf;

    if (p_editor->GetSelectedEntity() == node->entity)
        flags |= ImGuiTreeNodeFlags_Selected;

    bool open = ImGui::TreeNodeEx((void*) node->entity.get(), flags, node->entity->GetName().c_str());

    if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
    {
        p_editor->SetSelectedEntity(node->entity);
        if (m_inspectorPanel)
            m_inspectorPanel->SetSelectedEntity(node->entity);
    }

    if (ImGui::BeginDragDropSource())
    {
        Entity* rawEntityPtr = node->entity.get();
        ImGui::SetDragDropPayload("ENTITY_DRAG", &rawEntityPtr, sizeof(Entity*));
        ImGui::Text("Move %s", node->entity->GetName().c_str());
        ImGui::EndDragDropSource();
    }

    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ENTITY_DRAG"))
        {
            Entity* droppedRawPtr = *(Entity**) payload->Data;
            auto droppedEntity = p_editor->GetEngine()->GetEntityManager()->GetEntityByRawPointer(droppedRawPtr);

            if (droppedEntity != node->entity && !IsDescendant(droppedEntity, node->entity))
            {
                m_entityToReparent = droppedEntity;
                m_newParent = node->entity;
            }
        }
        ImGui::EndDragDropTarget();
    }

    if (ImGui::BeginPopupContextItem("EntityContextMenu"))
    {
        if (ImGui::MenuItem("Rename"))
        {
            m_entityToRename = node->entity;
            std::memset(m_renameBuffer, 0, sizeof(m_renameBuffer));
            strncpy_s(m_renameBuffer, m_entityToRename->GetName().c_str(), sizeof(m_renameBuffer) - 1);
            m_showRenamePopup = true;
        }

        if (ImGui::MenuItem("Delete"))
        {
            m_pendingDeletes.push_back(node->entity);
        }

        ImGui::EndPopup();
    }

    if (open)
    {
        for (const auto& child : node->children)
        {
            DrawEntityNode(child);
        }
        ImGui::TreePop();
    }
}


void HierarchyPanel::BuildHierarchy()
{
    m_rootEntities.clear();
    std::unordered_map<Entity*, std::shared_ptr<EntityNode>> nodeMap;

    const auto& allEntities = p_editor->GetEngine()->GetEntityManager()->GetEntities();

    for (const auto& entity : allEntities)
    {
        nodeMap[entity.get()] = std::make_shared<EntityNode>(entity);
    }

    for (const auto& entity : allEntities)
    {
        auto parent = entity->Transform()->GetParent();
        if (parent)
        {
            auto parentNodeIt = nodeMap.find(parent.get());
            if (parentNodeIt != nodeMap.end())
            {
                parentNodeIt->second->children.push_back(nodeMap[entity.get()]);
            }
        } else
        {
            m_rootEntities.push_back(nodeMap[entity.get()]);
        }
    }
}

bool HierarchyPanel::IsDescendant(const std::shared_ptr<Entity>& child, const std::shared_ptr<Entity>& parent) const
{
    auto currentParent = child->Transform()->GetParent();
    while (currentParent)
    {
        if (currentParent == parent)
            return true;
        currentParent = currentParent->Transform()->GetParent();
    }
    return false;
}

std::string HierarchyPanel::GenerateUniqueEntityName(const std::string& baseName)
{
    int suffix = 1;
    std::string finalName = baseName;
    auto& entities = p_editor->GetEngine()->GetEntityManager()->GetEntities();

    auto nameExists = [&entities](const std::string& name)
    {
        return std::any_of(entities.begin(), entities.end(), [&](const std::shared_ptr<Entity>& e)
                           { return e->GetName() == name; });
    };

    while (nameExists(finalName))
    {
        finalName = baseName + " (" + std::to_string(suffix++) + ")";
    }

    return finalName;
}
