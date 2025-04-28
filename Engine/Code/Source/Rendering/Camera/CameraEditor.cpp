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


    /*
    * LantualGL code
    	GLfloat velocity = moveSpeed * deltaTime;


	if (keys[GLFW_KEY_W]) {
		position += front * velocity;
	}
    
    */

    float l_velocity = m_movementSpeed * Time::GetDeltaTime();

    if (a_input->IsKeyDown(a_window, Key::KEY_W))
    {
        /*
        m_camEditorPosition.x--;
        m_camEditorPosition.x += -m_movementSpeed + Time::GetDeltaTime();*/

        m_camEditorPosition.x -=  l_velocity;
        DEBUG_LOG_VERBOSE("FORWARD : {}", Time::GetDeltaTime());
    }
    if (a_input->IsKeyDown(a_window, Key::KEY_S))
    {
        m_camEditorPosition.x += l_velocity;
       // m_camPosition.x = m_camPosition.x * m_movementSpeed * Time::GetDeltaTime();
        DEBUG_LOG_VERBOSE("BACKWARDS");
    }
    if (a_input->IsKeyDown(a_window, Key::KEY_A)) {
        m_camEditorPosition.y -= l_velocity;
    }
    if (a_input->IsKeyDown(a_window, Key::KEY_D)) {
        m_camEditorPosition.y += l_velocity;
    }

}
