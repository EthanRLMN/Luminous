#pragma once
#include "IInputManager.hpp"

#include "GLFW/glfw3.h"
#include "Utils/Exporter.hpp"

class IWindow;

class LUMINOUS_ENGINE_API GLFWInputManager final : public IInputManager
{
public:
    void Initialize(IWindow* a_window) override;

    int IsKeyDown(IWindow* a_window, int a_key) override;
    int IsKeyUp(IWindow* a_window, int a_key) override;
    int IsKeyPressed(IWindow* a_window, int a_key) override;

    int IsMouseButtonDown(IWindow* a_window, int a_button) override;
    int IsMouseButtonUp(IWindow* a_window, int a_button) override;
    int IsMouseButtonPressed(IWindow* a_window, int a_button) override;

    GLFWInputManager* CastGLFW() override { return this; }

private:
    static void KeyCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods);

    inline static int m_keyPressed[400];
    inline static std::array<int, 400> m_keyStatus;
};
