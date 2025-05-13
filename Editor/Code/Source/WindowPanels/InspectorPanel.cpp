#include "WindowPanels/InspectorPanel.hpp"

#include "imgui.h"

void MatrixToArray(const Maths::Matrix4& matrix, float out[16])
{
    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col)
            out[col + row * 4] = matrix.mat[row][col];
}

void InspectorPanel::SetSelectedEntity(const std::shared_ptr<Entity>& entity)
{
    p_isEntitySelected = entity;
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

        if (p_isEntitySelected)
        {
            if (ImGui::CollapsingHeader("Transform"))
            {
                Maths::Vector3 position = p_isEntitySelected->Transform()->GetLocalPosition();
                Maths::Quaternion rotationQuat = p_isEntitySelected->Transform()->GetLocalRotationQuat();
                Maths::Vector3 scale = p_isEntitySelected->Transform()->GetLocalScale();

                Maths::Vector3 rotation = rotationQuat.ToEulerAngles(true);

                ImGui::InputFloat3("Position", &position.x);
                ImGui::InputFloat3("Rotation", &rotation.x);
                ImGui::InputFloat3("Scale", &scale.x);

                p_isEntitySelected->Transform()->SetLocalPosition(position);
                p_isEntitySelected->Transform()->SetLocalRotationQuat(Maths::Quaternion::FromEulerAngles(rotation));
                p_isEntitySelected->Transform()->SetLocalScale(scale);
            }

            ImGuizmo::BeginFrame();

            Maths::Matrix4 transform = p_isEntitySelected->Transform()->GetLocalMatrix();
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

            p_isEntitySelected->Transform()->SetLocalPosition(newPosition);
            p_isEntitySelected->Transform()->SetLocalRotationQuat(Maths::Quaternion::FromEulerAngles(newEuler));
            p_isEntitySelected->Transform()->SetLocalScale(newScale);
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
