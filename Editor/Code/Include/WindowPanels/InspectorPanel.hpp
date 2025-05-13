#pragma once

#include "Interface/IWindowPanel.hpp"
#include "Game/Systems/Camera/CameraEditor.hpp"

class InspectorPanel : public IWindowPanel
{
public:
    explicit InspectorPanel(Editor* a_editor, const std::string& a_windowIdentifier) : IWindowPanel(a_editor, a_windowIdentifier) {};

    void Init() override {};
    void Update() override {};
    void Render() override;
    void Destroy() override {};

    void SetSelectedEntity(const std::shared_ptr<Entity>& entity);
    void GetSelectedEntity(const std::shared_ptr<Entity>& entity) { p_isEntitySelected = entity; }

    void MatrixToArray(const Maths::Matrix4& matrix, float out[16]);
    Maths::Matrix4 ArrayToMatrix(const float in[16]);
private:
    std::array<float, 16> ToFloatArray(const Maths::Matrix4& matrix);
    CameraEditor* m_camera = nullptr;
};
