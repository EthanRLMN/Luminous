#include "WindowPanels/HierarchyPanel.hpp"

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
        Light,
        Camera
    } selectedEntityTemplate = EntityTemplate::None;

    static char newEntityName[128] = "New Entity";

    if (ImGui::BeginPopupContextWindow("HierarchyContextMenu", ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems))
    {
        if (ImGui::BeginMenu("Add new Entity..."))
        {
            if (ImGui::MenuItem("Empty"))
            {
                selectedEntityTemplate = EntityTemplate::Empty;
                ImGui::OpenPopup("CreateEntityPopup");
            }
            if (ImGui::MenuItem("Light"))
            {
                selectedEntityTemplate = EntityTemplate::Light;
                ImGui::OpenPopup("CreateEntityPopup");
            }
            if (ImGui::MenuItem("Camera"))
            {
                selectedEntityTemplate = EntityTemplate::Camera;
                ImGui::OpenPopup("CreateEntityPopup");
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
            auto newEntity = entityManager->CreateEntity();
            newEntity->SetName(GenerateUniqueEntityName(newEntityName));

            // Create Components based on the selected template
            /*switch (selectedEntityTemplate)
            {
                case EntityTemplate::Camera:
                    newEntity->AddComponent<CameraComponent>();
                    break;
                case EntityTemplate::Light:
                    newEntity->AddComponent<LightComponent>();
                    break;
                case EntityTemplate::Empty:
                default:
                    break;
            }*/

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

    ImGui::End();
}

void HierarchyPanel::DrawEntityNode(const EntityNode& node)
{
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

    if (node.children.empty())
        flags |= ImGuiTreeNodeFlags_Leaf;

    if (p_isEntitySelected == node.entity)
        flags |= ImGuiTreeNodeFlags_Selected;

    bool open = ImGui::TreeNodeEx((void*) node.entity.get(), flags, node.entity->GetName().c_str());

    if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
    {
        p_isEntitySelected = node.entity;
    }

    if (ImGui::BeginDragDropSource())
    {
        std::shared_ptr<Entity> dragEntity = node.entity;
        ImGui::SetDragDropPayload("ENTITY_DRAG", &dragEntity, sizeof(std::shared_ptr<Entity>));
        ImGui::Text("Move %s", node.entity->GetName().c_str());
        ImGui::EndDragDropSource();
    }

    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ENTITY_DRAG"))
        {
            std::shared_ptr<Entity> droppedEntity = *(std::shared_ptr<Entity>*) payload->Data;

            if (droppedEntity != node.entity && !IsDescendant(node.entity, droppedEntity))
            {
                droppedEntity->SetParent(node.entity);
                BuildHierarchy();
            }
        }

        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FILE_DRAG"))
        {
            const char* droppedPath = static_cast<const char*>(payload->Data);
            std::string filePath(droppedPath);

            std::string extension = std::filesystem::path(filePath).extension().string();
            if (extension == ".png" || extension == ".jpg")
            {
                std::cout << "Texture dropped on entity: " << filePath << std::endl;
            }
        }

        ImGui::EndDragDropTarget();
    }

    if (open)
    {
        for (const auto& child : node.children)
        {
            DrawEntityNode(child);
        }
        ImGui::TreePop();
    }
}


void HierarchyPanel::BuildHierarchy()
{
    const std::vector<std::shared_ptr<Entity>> allEntities = p_editor->GetEngine()->GetEntityManager()->GetEntities();

    std::unordered_map<Entity*, EntityNode> entityNodeMap;

    for (const auto& entity : allEntities)
    {
        entityNodeMap[entity.get()] = EntityNode(entity);
    }

    m_rootEntities.clear();

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

bool HierarchyPanel::IsDescendant(const std::shared_ptr<Entity>& child, const std::shared_ptr<Entity>& parent) const
{
    auto current = child->GetParent();
    while (current)
    {
        if (current == parent)
            return true;
        current = current->GetParent();
    }
    return false;
}

std::string HierarchyPanel::GenerateUniqueEntityName(const std::string& baseName)
{
    int suffix = 1;
    std::string finalName = baseName;
    auto& entities = p_editor->GetEngine()->GetEntityManager()->GetEntities();

    auto nameExists = [&entities](const std::string& name) {
        return std::any_of(entities.begin(), entities.end(), [&](const std::shared_ptr<Entity>& e) {
            return e->GetName() == name;
        });
    };

    while (nameExists(finalName))
    {
        finalName = baseName + " (" + std::to_string(suffix++) + ")";
    }

    return finalName;
}