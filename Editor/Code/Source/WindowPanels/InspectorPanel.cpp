#include "WindowPanels/InspectorPanel.hpp"

#include "imgui.h"


void InspectorPanel::Render()
{
    IWindowPanel::Render();

    if (p_isOpen)
    {
        ImGui::Begin(p_windowIdentifier.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);

        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::MenuItem("Add Component"))
            {

            }
            ImGui::EndPopup();
        }

        if (selectedEntity)
        {
            if (ImGui::CollapsingHeader("Transform"))
            {
                Maths::Vector3 position = selectedEntity->GetPosition();
                Maths::Quaternion rotation = selectedEntity->GetRotation();
                Maths::Vector3 scale = selectedEntity->GetScale();

                ImGui::InputFloat3("Position", &position.x);
                ImGui::InputFloat3("Rotation", &rotation.x);
                ImGui::InputFloat3("Scale", &scale.x);

                selectedEntity->GetPosition() = position;
                selectedEntity->GetRotation() = rotation;
                selectedEntity->GetScale() = scale;
            }

        }

        if (selectedEntity)
        {
            ImGuizmo::BeginFrame();

            Maths::Matrix4 matrix = selectedEntity->GetTRS();

            ImVec2 pos = ImGui::GetCursorScreenPos();
            ImVec2 size = ImGui::GetContentRegionAvail();

            ImGuizmo::SetRect(pos.x, pos.y, size.x, size.y);

            float matrixArray[16] = { 0.0f };
            ToFloatArray(matrixArray);

            ImGuizmo::Manipulate(selectedEntity->GetTransform().GetViewMatrix().ToFloatArray(),
                                 selectedEntity->GetTransform().GetProjectionMatrix().ToFloatArray(),
                                 ImGuizmo::TRANSLATE | ImGuizmo::ROTATE | ImGuizmo::SCALE,
                                 ImGuizmo::LOCAL, matrixArray);

            Maths::Vector3 newPosition, newScale;
            Maths::Quaternion newRotation;
            ImGuizmo::DecomposeMatrixToComponents(matrixArray, &newPosition.x, &newRotation.x, &newScale.x);

            selectedEntity->SetPosition(newPosition);
            selectedEntity->SetRotation(newRotation);
            selectedEntity->SetScale(newScale);
        }

        ImGui::PopStyleColor();
        ImGui::End();
    }
}

std::array<float, 16> InspectorPanel::ToFloatArray(const Maths::Matrix4& matrix)
{
    std::array<float, 16> flatArray;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            flatArray[i * 4 + j] = matrix.mat[i][j];
        }
    }
    return flatArray;
}
