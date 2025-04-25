#include "Rendering/Camera/CameraEditor.hpp"

void CameraEditor::InitCameraEditor(IWindow* a_window , float a_aspectRatio)
{
    aspectRatio = a_aspectRatio;
}

void CameraEditor::CameraEditorUpdate()
{
    m_projectionMatrix = UpdateProjectionMatrix();
    m_viewMatrix = UpdateViewMatrix();
}


void CameraEditor::CameraInputUpdate(IWindow* a_window)
{
    /*
    if (GLFWInputManager::IsKeyPressed(Key::KEY_F17))
    {

    }*/
}
