#include "Rendering/Camera/CameraEditor.hpp"
#include "Core/GLFW/GLFWWindow.hpp"
#include "Game/Systems/Time.inl"


void CameraEditor::Init(const float a_aspectRatio, const float a_fov, const float a_nearPlane, const float a_farPlane)
{
    m_aspectRatio = a_aspectRatio;
    m_fov = a_fov;
    m_nearPlane = a_nearPlane;
    m_farPlane = a_farPlane;
}

void CameraEditor::Update(const float a_aspectRatio)
{
    m_aspectRatio = a_aspectRatio;
    UpdateVectors();
    m_viewMatrix = UpdateViewMatrix(m_eye, m_center, m_up);
    m_projectionMatrix = UpdateProjectionMatrix(m_fov, m_aspectRatio, m_nearPlane, m_farPlane);
}


void CameraEditor::UpdateInput(IInputManager* a_input)
{
    MovementHandler(a_input);
    MouseHandler(a_input);
    SpeedHandler(a_input);
}

void CameraEditor::MovementHandler(IInputManager* a_input)
{
    const float l_velocity = m_movementSpeed * Time::GetDeltaTime();

    if (a_input->IsKeyDown(Key::KEY_W))
    {
        m_eye += m_forward * l_velocity;
        m_center += m_forward * l_velocity;
    }

    if (a_input->IsKeyDown(Key::KEY_S))
    {
        m_eye -= m_forward * l_velocity;
        m_center -= m_forward * l_velocity;
    }

    if (a_input->IsKeyDown(Key::KEY_A))
    {
        m_eye -= m_right * l_velocity;
        m_center -= m_right * l_velocity;
    }

    if (a_input->IsKeyDown(Key::KEY_D))
    {
        m_eye += m_right * l_velocity;
        m_center += m_right * l_velocity;
    }

    if (a_input->IsKeyDown(Key::KEY_Q))
    {
        m_eye -= m_up * l_velocity;
        m_center -= m_up * l_velocity;
    }

    if (a_input->IsKeyDown(Key::KEY_E))
    {
        m_eye += m_up * l_velocity;
        m_center += m_up * l_velocity;
    }
}

void CameraEditor::MouseHandler(IInputManager* a_input)
{
    if (a_input->IsMouseButtonDown(MouseButton::MOUSE_BUTTON_RIGHT))
    {
        a_input->ConfigureMouseInput(CursorInputMode::CAPTURED);

        const Maths::Vector2 l_mouseDelta = a_input->GetMouseDelta();
        const float l_sensitivity = 0.1f;

        m_yaw += l_mouseDelta.x * l_sensitivity;
        m_pitch -= l_mouseDelta.y * l_sensitivity;
        m_pitch = std::clamp(m_pitch, -89.0f, 89.0f);

        Maths::Vector3 l_direction { Maths::Vector3::Zero };
        l_direction.x = cos(Maths::DegToRad(m_yaw)) * cos(Maths::DegToRad(m_pitch));
        l_direction.y = sin(Maths::DegToRad(m_pitch));
        l_direction.z = sin(Maths::DegToRad(m_yaw)) * cos(Maths::DegToRad(m_pitch));
        l_direction = l_direction.Normalize();

        const Maths::Vector3 l_worldUp = Maths::Vector3(0.0f, 1.0f, 0.0f);
        m_right = l_direction.CrossProduct(l_worldUp).Normalize();
        m_up = m_right.CrossProduct(l_direction).Normalize();

        m_viewMatrix = Maths::Matrix4::LookAt(m_eye, m_eye + l_direction, l_worldUp);
    }
    else if (a_input->IsMouseButtonUp(MouseButton::MOUSE_BUTTON_RIGHT))
        a_input->ConfigureMouseInput(CursorInputMode::NORMAL);
}

void CameraEditor::SpeedHandler(IInputManager* a_input)
{
    const Maths::Vector2 l_scroll{ a_input->GetMouseScroll() };
    if (a_input->IsKeyDown(Key::KEY_LEFT_CONTROL))
    {
        if (l_scroll.y > 0.0f)
            m_movementSpeed += m_cameraSpeed;

        else if (l_scroll.y < 0.0f)
            m_movementSpeed -= m_cameraSpeed;

        if (m_movementSpeed < 0.1f)
            m_movementSpeed = 0.1f;
    }
}

void CameraEditor::UpdateVectors()
{
    m_forward = (m_center - m_eye).Normalize();
    m_right = m_forward.CrossProduct(m_up).Normalize();
    m_up = m_right.CrossProduct(m_forward).Normalize();
}

