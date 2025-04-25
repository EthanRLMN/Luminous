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

    //CameraEditor(float a_aspectRatio);

    void InitCameraEditor(IWindow* a_window, float a_aspectRatio);
    void CameraInputUpdate(IWindow* a_window);
    // void CameraInputUpdate(IWindow* a_window);

private:

};

