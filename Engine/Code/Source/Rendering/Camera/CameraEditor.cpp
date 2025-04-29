#include "Rendering/Camera/CameraEditor.hpp"
#include "Core/GLFW/GLFWWindow.hpp"
#include "Game/Systems/Time.inl"
#include "MathUtils.hpp"


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

void CameraEditor::Update(float a_aspectRatio)
{
    aspectRatio = a_aspectRatio;

  

    m_position = m_camPosition;

    m_direction = m_camDirection.Normalize();
    m_up = m_camUp;

    
    m_viewMatrix = m_viewMatrix = UpdateViewMatrixCustom(m_camPosition, m_camPosition + m_camDirection, m_camUp);
    m_projectionMatrix = UpdateProjectionMatrixCustom(fov,aspectRatio,nearPlane,farPlane);


    DEBUG_LOG_VERBOSE("Camera Editor : Position X {} , Y {} , Z {}" , m_camPosition.x ,m_camPosition.y , m_camPosition.z);
   // DEBUG_LOG_VERBOSE("Camera Editor : Rotation X {} , Y {} , Z {}", m_camDirection.x, m_camDirection.y, m_camDirection.z);

}


void CameraEditor::UpdateInput(IWindow* a_window, IInputManager* a_input)
{
    MovementHandler(a_window, a_input, m_movementSpeed);
    MouseHandler(a_window, a_input);
    SpeedHandler(a_window, a_input, m_cameraSpeed, m_movementSpeed);
}

void CameraEditor::MovementHandler(IWindow* a_window, IInputManager* a_input, float a_movementSpeed)
{
    float l_velocity = a_movementSpeed * Time::GetDeltaTime();
    m_right = m_direction.CrossProduct(m_camUp).Normalize();




    if (a_input->IsKeyDown(a_window, Key::KEY_W))
    {
        m_camPosition.x += l_velocity;
        m_velocity += m_camDirection * a_movementSpeed;
        DEBUG_LOG_VERBOSE("Camera Editor : FORWARD");
    }
    if (a_input->IsKeyDown(a_window, Key::KEY_S))
    {
        m_camPosition.x -= l_velocity;
        m_velocity -= m_camDirection * a_movementSpeed;
        DEBUG_LOG_VERBOSE("Camera Editor : BACKWARDS");
    }

    if (a_input->IsKeyDown(a_window, Key::KEY_A))
    {
        m_camPosition.y -= l_velocity;
        m_velocity += (m_direction.CrossProduct(m_camUp).Normalize() * -1) * a_movementSpeed;
        DEBUG_LOG_VERBOSE("Camera Editor : LEFT");
    }
    if (a_input->IsKeyDown(a_window, Key::KEY_D))
    {
        m_camPosition.y +=  l_velocity;
        m_velocity -= m_direction.CrossProduct(m_camUp).Normalize() * a_movementSpeed;
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


        //m_camDirection = m_camDirection.RotateAroundAxis(m_right, rotationX);
       // m_camDirection = m_camDirection.RotateAroundAxis(m_camUp, rotationY);


        m_right = m_direction.CrossProduct(m_camUp).Normalize();

        m_viewMatrix = UpdateViewMatrixCustom(m_camPosition, m_camPosition + m_camDirection, m_camUp);

       // DEBUG_LOG_VERBOSE("Camera Editor : Rotation X {} , Y {} , Z {}", m_camDirection.x, m_camDirection.y, m_camDirection.z);
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

