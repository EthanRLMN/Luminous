#include "WindowPanels/InspectorPanel.hpp"

#include "imgui.h"

void InspectorPanel::MatrixToArray(const Maths::Matrix4& matrix, float out[16])
{
    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col)
            out[col + row * 4] = matrix.mat[row][col];
}

void InspectorPanel::SetSelectedEntity(const std::shared_ptr<Entity>& entity)
{
    p_isEntitySelected = entity;
}

Maths::Matrix4 InspectorPanel::ArrayToMatrix(const float in[16])
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
                Maths::Vector3 rotation = p_isEntitySelected->Transform()->GetLocalRotationVec();
                Maths::Vector3 scale = p_isEntitySelected->Transform()->GetLocalScale();

                if (ImGui::InputFloat3("Position", &position.x))
                  p_isEntitySelected->Transform()->SetLocalPosition(position);

                ImGui::InputFloat3("Rotation", &rotation.x);
                ImGui::InputFloat3("Scale", &scale.x);

                p_isEntitySelected->Transform()->SetLocalRotationVec(rotation);
                p_isEntitySelected->Transform()->SetLocalScale(scale);
            }
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
