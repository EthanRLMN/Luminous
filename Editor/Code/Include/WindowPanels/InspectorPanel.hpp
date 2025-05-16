#pragma once

#include "Interface/IWindowPanel.hpp"
#include "imguizmo/ImGuizmo.h"
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
private:
    std::array<float, 16> ToFloatArray(const Maths::Matrix4& matrix);
    CameraEditor* m_camera = nullptr;
};
