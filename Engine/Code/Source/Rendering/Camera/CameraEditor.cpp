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
    //m_forward = Maths::Vector3{ cos(m_center) * cos(yaw), sin(pitch), −cos(pitch) * sin(yaw) };

    //DEBUG_LOG_VERBOSE("Camera Editor : Position X {} , Y {} , Z {}" , m_eye.x ,m_eye.y , m_eye.z);
}


void CameraEditor::UpdateInput(IWindow* a_window, IInputManager* a_input)
{
    MovementHandler(a_window, a_input);
    MouseHandler(a_window, a_input);
    SpeedHandler(a_window, a_input);
}

void CameraEditor::MovementHandler(IWindow* a_window, IInputManager* a_input)
{
    const float l_velocity = m_movementSpeed * Time::GetDeltaTime();

    if (a_input->IsKeyDown(a_window, Key::KEY_W))
    {
        m_eye += m_forward * l_velocity;
        m_center += m_forward * l_velocity;
    }

    if (a_input->IsKeyDown(a_window, Key::KEY_S))
    {
        m_eye -= m_forward * l_velocity;
        m_center -= m_forward * l_velocity;
    }

    if (a_input->IsKeyDown(a_window, Key::KEY_A))
    {
        m_eye -= m_right * l_velocity;
        m_center -= m_right * l_velocity;
    }

    if (a_input->IsKeyDown(a_window, Key::KEY_D))
    {
        m_eye += m_right * l_velocity;
        m_center += m_right * l_velocity;
    }

    if (a_input->IsKeyDown(a_window, Key::KEY_Q))
    {
        m_eye -= m_up * l_velocity;
        m_center -= m_up * l_velocity;
    }

    if (a_input->IsKeyDown(a_window, Key::KEY_E))
    {
        m_eye += m_up * l_velocity;
        m_center += m_up * l_velocity;
    }
}

void CameraEditor::MouseHandler(IWindow* a_window, IInputManager* a_input)
{
    if (a_input->IsMouseButtonDown(a_window, MouseButton::MOUSE_BUTTON_2))
    {
        m_viewMatrix = UpdateViewMatrix(m_eye, m_eye + m_center, m_up);
    }
}

void CameraEditor::SpeedHandler(IWindow* a_window, IInputManager* a_input)
{
    const Maths::Vector2 l_scroll{ a_input->GetMouseScroll() };
    if (a_input->IsKeyDown(a_window, Key::KEY_LEFT_CONTROL))
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

