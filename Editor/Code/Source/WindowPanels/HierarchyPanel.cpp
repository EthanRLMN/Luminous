#include "WindowPanels/HierarchyPanel.hpp"

#include <iostream>

void HierarchyPanel::Render()
{
    IWindowPanel::Render();

    if (!p_isOpen)
        return;

    ImGui::Begin(p_windowIdentifier.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);

    m_rootEntities.clear();

    static enum class EntityTemplate {
        None,
        Empty,
        Cube,
        Plane,
        Sphere,
        Cone,
        Cylinder,
        Capsule,
        Monkey,
        Companion
    } selectedEntityTemplate = EntityTemplate::None;

    static char newEntityName[128] = "New Entity";

    if (ImGui::BeginPopupContextWindow("HierarchyContextMenu", ImGuiPopupFlags_MouseButtonRight))
    {
        if (ImGui::BeginMenu("Add new Entity..."))
        {
            if (ImGui::MenuItem("Empty"))
            {
                selectedEntityTemplate = EntityTemplate::Empty;
                ImGui::OpenPopup("CreateEntityPopup");
                p_editor->GetEngine()->GetEntityManager()->CreateEntityFromTemplate("DefaultEmpty");
            }
            if (ImGui::MenuItem("Cube"))
            {
                selectedEntityTemplate = EntityTemplate::Cube;
                ImGui::OpenPopup("CreateEntityPopup");
                p_editor->GetEngine()->GetEntityManager()->CreateEntityFromTemplate("DefaultCube");
            }
            if (ImGui::MenuItem("Plane"))
            {
                selectedEntityTemplate = EntityTemplate::Plane;
                ImGui::OpenPopup("CreateEntityPopup");
                p_editor->GetEngine()->GetEntityManager()->CreateEntityFromTemplate("DefaultPlane");
            }
            if (ImGui::MenuItem("Sphere"))
            {
                selectedEntityTemplate = EntityTemplate::Sphere;
                ImGui::OpenPopup("CreateEntityPopup");
                p_editor->GetEngine()->GetEntityManager()->CreateEntityFromTemplate("DefaultSphere");
            }
            if (ImGui::MenuItem("Cone"))
            {
                selectedEntityTemplate = EntityTemplate::Cone;
                ImGui::OpenPopup("CreateEntityPopup");
                p_editor->GetEngine()->GetEntityManager()->CreateEntityFromTemplate("DefaultCone");    
            }
            if (ImGui::MenuItem("Cylinder"))
            {
                selectedEntityTemplate = EntityTemplate::Cylinder;
                ImGui::OpenPopup("CreateEntityPopup");
                p_editor->GetEngine()->GetEntityManager()->CreateEntityFromTemplate("DefaultCylinder");
            }
            if (ImGui::MenuItem("Capsule"))
            {
                selectedEntityTemplate = EntityTemplate::Capsule;
                ImGui::OpenPopup("CreateEntityPopup");
                p_editor->GetEngine()->GetEntityManager()->CreateEntityFromTemplate("DefaultCapsule");
            }
            if (ImGui::MenuItem("Monkey"))
            {
                selectedEntityTemplate = EntityTemplate::Monkey;
                ImGui::OpenPopup("CreateEntityPopup");
                p_editor->GetEngine()->GetEntityManager()->CreateEntityFromTemplate("DefaultMonkey");
            }
            if (ImGui::MenuItem("Companion"))
            {
                selectedEntityTemplate = EntityTemplate::Companion;
                ImGui::OpenPopup("CreateEntityPopup");
                p_editor->GetEngine()->GetEntityManager()->CreateEntityFromTemplate("DefaultCompanion");
            }
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
            auto newEntity = entityManager->CreateEntityFromTemplate("Companion");
            newEntity->SetName(GenerateUniqueEntityName(newEntityName));

            selectedEntityTemplate = EntityTemplate::None;
            std::memset(newEntityName, 0, sizeof(newEntityName));
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            selectedEntityTemplate = EntityTemplate::None;
            std::memset(newEntityName, 0, sizeof(newEntityName));
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    BuildHierarchy();

    for (const auto& root : m_rootEntities)
    {
        DrawEntityNode(root);
    }

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
        ImVec2 detachZoneSize = ImVec2(avail.x, avail.y);

        ImGui::SetCursorPosY(ImGui::GetCursorPosY());
        ImGui::InvisibleButton("##DetachZone", detachZoneSize);

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
    ImGui::End();
}

void HierarchyPanel::DrawEntityNode(const std::shared_ptr<EntityNode>& node)
{
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
