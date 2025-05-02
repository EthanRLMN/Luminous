#include "Rendering/Camera/CameraEditor.hpp"

#include "MathUtils.hpp"
#include "Core/GLFW/GLFWWindow.hpp"
#include "Game/Systems/Time.inl"


void CameraEditor::Init(const float a_aspectRatio, const float a_fov, const float a_nearPlane, const float a_farPlane)
{
    m_aspectRatio = a_aspectRatio;
    m_fov = a_fov;
    m_nearPlane = a_nearPlane;
    m_farPlane = a_farPlane;

    m_worldForward = (m_center - m_eye).Normalize();
    m_worldRight = m_worldForward.CrossProduct(m_worldUp).Normalize();
    m_worldUp = m_worldRight.CrossProduct(m_worldForward).Normalize();
}

void CameraEditor::Update(const float a_aspectRatio)
{
    m_aspectRatio = a_aspectRatio;
    m_viewMatrix = UpdateViewMatrix(m_eye, m_center, m_worldUp);
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
        m_eye += m_localForward * l_velocity;
        m_center += m_localForward * l_velocity;
    }

    if (a_input->IsKeyDown(Key::KEY_S))
    {
        m_eye -= m_localForward * l_velocity;
        m_center -= m_localForward * l_velocity;
    }

    if (a_input->IsKeyDown(Key::KEY_A))
    {
        m_eye -= m_localRight * l_velocity;
        m_center -= m_localRight * l_velocity;
    }

    if (a_input->IsKeyDown(Key::KEY_D))
    {
        m_eye += m_localRight * l_velocity;
        m_center += m_localRight * l_velocity;
    }

    if (a_input->IsKeyDown(Key::KEY_Q))
    {
        m_eye -= m_worldUp * l_velocity;
        m_center -= m_worldUp * l_velocity;
    }

    if (a_input->IsKeyDown(Key::KEY_E))
    {
        m_eye += m_worldUp * l_velocity;
        m_center += m_worldUp * l_velocity;
    }
}

void CameraEditor::MouseHandler(IInputManager* a_input)
{
    const float l_velocity = m_mouseSensitivity * Time::GetDeltaTime();

    if (a_input->IsMouseButtonDown(MouseButton::MOUSE_BUTTON_RIGHT))
    {
        if (!m_isRotating)
        {
            a_input->ConfigureMouseInput(CursorInputMode::DISABLED);
            a_input->ResetMouseDelta();
            m_isRotating = true;
        }

        const Maths::Vector2 l_mouseDelta = a_input->GetMouseDelta();

        m_yaw += l_mouseDelta.x * l_velocity;
        m_pitch -= l_mouseDelta.y * l_velocity;
        m_pitch = std::clamp(m_pitch, -89.0f, 89.0f);
    }
    
    else if (a_input->IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_RIGHT))
    {
        a_input->ConfigureMouseInput(CursorInputMode::NORMAL);
        m_isRotating = false;
    }

    const float l_yawRad = Maths::DegToRad(m_yaw);
    const float l_pitchRad = Maths::DegToRad(m_pitch);

    Maths::Vector3 l_direction = Maths::Vector3::Zero;
    l_direction.x = cos(l_yawRad) * cos(l_pitchRad);
    l_direction.y = sin(l_pitchRad);
    l_direction.z = sin(l_yawRad) * cos(l_pitchRad);
    l_direction = l_direction.Normalize();

    m_localForward = l_direction;
    m_localRight = m_localForward.CrossProduct(m_worldUp).Normalize();
    m_localUp = m_localRight.CrossProduct(m_localForward).Normalize();

    m_viewMatrix = Maths::Matrix4::LookAt(m_eye, m_eye + m_localForward, m_worldUp);
}

void CameraEditor::SpeedHandler(IInputManager* a_input)
{
    const Maths::Vector2 l_scroll{ a_input->GetMouseScroll() };

    if (a_input->IsKeyDown(Key::KEY_LEFT_SHIFT))
        m_movementSpeed = m_dynamicSpeed * 5.0f;
    if (a_input->IsKeyReleased(Key::KEY_LEFT_SHIFT))
        m_movementSpeed = m_dynamicSpeed;

    if (a_input->IsKeyDown(Key::KEY_LEFT_CONTROL))
    {
        if (l_scroll.y > 0.0f)
            m_dynamicSpeed += m_speedMultiplier;

        else if (l_scroll.y < 0.0f)
            m_dynamicSpeed -= m_speedMultiplier;

        m_dynamicSpeed = std::clamp(m_dynamicSpeed, 0.1f, 10.0f);
        m_speedMultiplier = std::clamp(m_speedMultiplier, 0.1f, 10.0f);
    }
}

