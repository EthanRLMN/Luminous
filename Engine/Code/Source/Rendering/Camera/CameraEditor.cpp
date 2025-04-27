#include "Rendering/Camera/CameraEditor.hpp"

#include "Game/Systems/Time.inl"


void CameraEditor::Init(IWindow* a_window, const float a_aspectRatio, const float a_fov, const float a_nearPlane, const float a_farPlane)
{
    aspectRatio = a_aspectRatio;
    fov = a_fov;
    nearPlane = a_nearPlane;
    farPlane = a_farPlane;

    m_position = m_camPosition;
    m_direction = m_camDirection;
    m_up = m_camUp;
}

void CameraEditor::Update()
{
    m_position = m_camPosition;
    m_direction = m_camDirection;
    m_up = m_camUp;

    m_viewMatrix = UpdateViewMatrix();
    m_projectionMatrix = UpdateProjectionMatrix();
}


void CameraEditor::UpdateInput(IWindow* a_window, IInputManager* a_input)
{
    if (a_input->IsKeyDown(a_window, Key::KEY_W))
    {
        m_camPosition.x *= -m_movementSpeed * Time::GetDeltaTime();
        DEBUG_LOG_VERBOSE("FORWARD : {}", Time::GetDeltaTime());
    }
    if (a_input->IsKeyDown(a_window, Key::KEY_S))
    {
        //m_positionCameraEditor.x++;
        m_camPosition.x = m_camPosition.x * m_movementSpeed * Time::GetDeltaTime();
        DEBUG_LOG_VERBOSE("BACKWARDS");
    }
    if (a_input->IsKeyDown(a_window, Key::KEY_A)) {}
    if (a_input->IsKeyDown(a_window, Key::KEY_D)) {}

}
