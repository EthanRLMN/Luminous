#include "WindowPanels/InspectorPanel.hpp"

#include "imgui.h"

void MatrixToArray(const Maths::Matrix4& matrix, float out[16])
{
    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col)
            out[col + row * 4] = matrix.mat[row][col];
}

Maths::Matrix4 ArrayToMatrix(const float in[16])
{
    Maths::Matrix4 result;
    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col)
            result.mat[row][col] = in[col + row * 4];
    return result;
}

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
                Maths::Quaternion rotationQuat = selectedEntity->GetRotation();
                Maths::Vector3 scale = selectedEntity->GetScale();

                Maths::Vector3 rotation = rotationQuat.ToEulerAngles(true);

                ImGui::InputFloat3("Position", &position.x);
                ImGui::InputFloat3("Rotation", &rotation.x);
                ImGui::InputFloat3("Scale", &scale.x);

                selectedEntity->SetPosition(position);
                selectedEntity->SetRotation(Maths::Quaternion::FromEulerAngles(rotation));
                selectedEntity->SetScale(scale);
            }

            ImGuizmo::BeginFrame();

            Maths::Matrix4 transform = selectedEntity->GetTRS();
            float matrixArray[16];
            MatrixToArray(transform, matrixArray);

            ImVec2 pos = ImGui::GetCursorScreenPos();
            ImVec2 size = ImGui::GetContentRegionAvail();
            ImGuizmo::SetRect(pos.x, pos.y, size.x, size.y);

            float view[16];
            float projection[16];

            ImGuizmo::Manipulate(view, projection,
                                 ImGuizmo::TRANSLATE | ImGuizmo::ROTATE | ImGuizmo::SCALE,
                                 ImGuizmo::LOCAL, matrixArray);

            Maths::Vector3 newPosition, newEuler, newScale;
            ImGuizmo::DecomposeMatrixToComponents(matrixArray, &newPosition.x, &newEuler.x, &newScale.x);

            selectedEntity->SetPosition(newPosition);
            selectedEntity->SetRotation(Maths::Quaternion::FromEulerAngles(newEuler));
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
