#include "Rendering/Camera/CameraEditor.hpp"

void CameraEditor::InitCameraEditor(IWindow* a_window , float a_aspectRatio,float a_fov,float a_nearPlane,float a_farPlane)
{
    aspectRatio = a_aspectRatio;
    fov = a_fov;
    nearPlane = a_nearPlane;
    farPlane = a_farPlane;

    m_position = m_positionCameraEditor;
    m_direction = m_directionCameraEditor;
    m_up = m_upCameraEditor;
}

void CameraEditor::CameraEditorUpdate()
{
    m_viewMatrix = UpdateViewMatrix();
    m_projectionMatrix = UpdateProjectionMatrix();
}


void CameraEditor::CameraInputUpdate(IWindow* a_window,IInputManager* a_input)
{
        DEBUG_LOG_ERROR("TEST");
}
