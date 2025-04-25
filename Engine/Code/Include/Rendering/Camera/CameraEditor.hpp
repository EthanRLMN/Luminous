#pragma once
#include "Camera.hpp"
#include "Core/GLFW/GLFWInputManager.hpp"
#include "IInputManager.hpp"
#include "IWindow.hpp"

class CameraEditor : Camera
{
public:
    CameraEditor() {};
    ~CameraEditor() {};

    void InitCameraEditor(IWindow* a_window, float a_aspectRatio);
    // void CameraInputUpdate(IWindow* a_window);

private:
};

