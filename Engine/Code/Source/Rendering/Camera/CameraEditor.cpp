#include "Rendering/Camera/CameraEditor.hpp"
#include "Core/GLFW/GLFWWindow.hpp"
#include "Game/Systems/Time.inl"


void CameraEditor::Init(const float& a_aspectRatio, const float& a_fov, const float& a_nearPlane, const float& a_farPlane)
{
    m_aspectRatio = a_aspectRatio;
    m_fov = a_fov;
    m_nearPlane = a_nearPlane;
    m_farPlane = a_farPlane;
}

void CameraEditor::Update(const float a_aspectRatio)
{
    m_aspectRatio = a_aspectRatio;
    m_viewMatrix = UpdateViewMatrix(m_eye, m_center, m_up);
    m_projectionMatrix = UpdateProjectionMatrix(m_fov, m_aspectRatio, m_nearPlane, m_farPlane);
    //m_forward = Maths::Vector3{ cos(m_center) * cos(yaw), sin(pitch), −cos(pitch) * sin(yaw) };

    //DEBUG_LOG_VERBOSE("Camera Editor : Position X {} , Y {} , Z {}" , m_eye.x ,m_eye.y , m_eye.z);
}


void CameraEditor::UpdateInput(IWindow* a_window, IInputManager* a_input)
{
    MovementHandler(a_window, a_input, m_movementSpeed);
    MouseHandler(a_window, a_input);
    SpeedHandler(a_window, a_input, m_cameraSpeed, m_movementSpeed);
}

void CameraEditor::MovementHandler(IWindow* a_window, IInputManager* a_input, float a_movementSpeed)
{
    const float l_velocity = a_movementSpeed * Time::GetDeltaTime();
    m_right = m_center.CrossProduct(m_up).Normalize();

    if (a_input->IsKeyDown(a_window, Key::KEY_W))
    {
        m_eye += l_velocity;
        m_center += l_velocity;
        DEBUG_LOG_VERBOSE("Camera Editor : FORWARD");
    }
    if (a_input->IsKeyDown(a_window, Key::KEY_S))
    {
        m_eye -= l_velocity;
        m_center -= l_velocity;
        DEBUG_LOG_VERBOSE("Camera Editor : BACKWARDS");
    }

    if (a_input->IsKeyDown(a_window, Key::KEY_A))
    {
        m_eye += l_velocity;
        m_center += l_velocity;
        DEBUG_LOG_VERBOSE("Camera Editor : LEFT");
    }
    if (a_input->IsKeyDown(a_window, Key::KEY_D))
    {
        m_eye.y +=  l_velocity;
        DEBUG_LOG_VERBOSE("Camera Editor : RIGHT");
    }
}

void CameraEditor::MouseHandler(IWindow* a_window, IInputManager* a_input)
{
    if (a_input->IsMouseButtonDown(a_window, MouseButton::MOUSE_BUTTON_2))
    {
        Maths::Vector2 mouseDelta = a_input->GetMouseDelta(a_window);

        const float sensitivity = 0.1f;


        float rotationX = mouseDelta.y * sensitivity;
        float rotationY = mouseDelta.x * sensitivity;


        //m_center = m_center.RotateAroundAxis(m_right, rotationX);
       // m_center = m_center.RotateAroundAxis(m_up, rotationY);


        m_right = m_center.CrossProduct(m_up).Normalize();

        m_viewMatrix = UpdateViewMatrix(m_eye, m_eye + m_center, m_up);

       // DEBUG_LOG_VERBOSE("Camera Editor : Rotation X {} , Y {} , Z {}", m_center.x, m_center.y, m_center.z);
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

