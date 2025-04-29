#include "Rendering/Camera/CameraEditor.hpp"
#include "Game/Systems/Time.inl"


void CameraEditor::Init(IWindow* a_window, const float& a_aspectRatio, const float& a_fov, const float& a_nearPlane, const float& a_farPlane)
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
    MovementHandler(a_window, a_input, m_movementSpeed);
    RotationHandler(a_window, a_input);
    SpeedHandler(a_window, a_input, m_cameraSpeed, m_movementSpeed);
}

void CameraEditor::MovementHandler(IWindow* a_window, IInputManager* a_input, const float a_movementSpeed)
{
    const float l_velocity = a_movementSpeed * Time::GetDeltaTime();

    const Maths::Vector3 l_forward = m_direction.Normalize();
    const Maths::Vector3 l_right = Maths::Vector3::CrossProduct(l_forward, m_up).Normalize();

    if (a_input->IsKeyDown(a_window, Key::KEY_W))
        m_camPosition += l_forward * l_velocity;

    if (a_input->IsKeyDown(a_window, Key::KEY_S))
        m_camPosition -= l_forward * l_velocity;

    if (a_input->IsKeyDown(a_window, Key::KEY_A))
        m_camPosition -= l_right * l_velocity;

    if (a_input->IsKeyDown(a_window, Key::KEY_D))
        m_camPosition += l_right * l_velocity;
}

void CameraEditor::RotationHandler(IWindow* a_window, IInputManager* a_input)
{
    if (a_input->IsMouseButtonDown(a_window, MouseButton::MOUSE_BUTTON_2))
    {
        a_input->GetMouseDelta(a_window);
    }
}

void CameraEditor::SpeedHandler(IWindow* a_window, IInputManager* a_input, const float& a_cameraSpeed, float& a_movementSpeed)
{
    const Maths::Vector2 l_scroll{ a_input->GetMouseScroll() };
    if (a_input->IsKeyDown(a_window, Key::KEY_LEFT_CONTROL))
    {
        if (l_scroll.y > 0.0f)
            a_movementSpeed += a_cameraSpeed;

        else if (l_scroll.y < 0.0f)
            a_movementSpeed -= a_cameraSpeed;

        if (a_movementSpeed < 0.1f)
            a_movementSpeed = 0.1f;
    }
}
