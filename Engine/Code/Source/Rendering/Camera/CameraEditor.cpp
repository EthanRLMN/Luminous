#include "Rendering/Camera/CameraEditor.hpp"

#include "Game/Systems/Time.inl"


void CameraEditor::Init(IWindow* a_window, const float a_aspectRatio, const float a_fov, const float a_nearPlane, const float a_farPlane)
{
    aspectRatio = a_aspectRatio;
    fov = a_fov;
    nearPlane = a_nearPlane;
    farPlane = a_farPlane;

    m_position = m_camEditorPosition;
    m_direction = m_camEditorDirection;
    m_up = m_camEditorUp;
}

void CameraEditor::Update()
{
    m_position = m_camEditorPosition;
    m_direction = m_camEditorDirection;
    m_up = m_camEditorUp;

    m_viewMatrix = UpdateViewMatrix();
    m_projectionMatrix = UpdateProjectionMatrix();
}


void CameraEditor::UpdateInput(IWindow* a_window, IInputManager* a_input)
{
    MovementCamera(a_window, a_input, m_movementSpeed);
    TurnCamera(a_window, a_input, m_cameraSpeed);
}

void CameraEditor::MovementCamera(IWindow* a_window, IInputManager* a_input, float a_movementSpeed)
{
    float l_velocity = a_movementSpeed * Time::GetDeltaTime();

    if (a_input->IsKeyDown(a_window, Key::KEY_W))
    {
        m_camEditorPosition.x -= l_velocity;
        DEBUG_LOG_VERBOSE("Camera Editor : FORWARD : {}", Time::GetDeltaTime());
    }
    if (a_input->IsKeyDown(a_window, Key::KEY_S))
    {
        m_camEditorPosition.x += l_velocity;
        DEBUG_LOG_VERBOSE("Camera Editor : BACKWARDS");
    }
    if (a_input->IsKeyDown(a_window, Key::KEY_A))
    {
        m_camEditorPosition.y -= l_velocity;
        DEBUG_LOG_VERBOSE("Camera Editor : LEFT");
    }
    if (a_input->IsKeyDown(a_window, Key::KEY_D))
    {
        m_camEditorPosition.y += l_velocity;
        DEBUG_LOG_VERBOSE("Camera Editor : RIGHT");
    }
}

void CameraEditor::TurnCamera(IWindow* a_window, IInputManager* a_input, float a_cameraSpeed)
{

    if (a_input->IsMouseButtonDown(a_window, MouseButton::MOUSE_BUTTON_2)) {
        DEBUG_LOG_VERBOSE("Camera Editor : Mouse Right CLick");






    }
}
