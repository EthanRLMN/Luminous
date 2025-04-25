#pragma once
#include "Camera.hpp"
#include "Core/GLFW/GLFWInputManager.hpp"
#include "IInputManager.hpp"
#include "IWindow.hpp"

class CameraEditor : public Camera
{
public:
    CameraEditor() {};
    ~CameraEditor() {};

 

    void InitCameraEditor(IWindow* a_window, float a_aspectRatio);
    void CameraEditorUpdate();
    void CameraInputUpdate(IWindow* a_window);
    // void CameraInputUpdate(IWindow* a_window);


    Maths::Matrix4 m_projectionMatrix = Maths::Matrix4::identity;
    Maths::Matrix4 m_viewMatrix = Maths::Matrix4::identity;

private:

};

