#include "IWindow.hpp"

#include "Core/GLFW/GLFWInputManager.hpp"
#include "Core/GLFW/GLFWWindow.hpp"

std::array<int, 349> GLFWInputManager::s_keyPressed { };
std::array<Action, 349> GLFWInputManager::s_keyStatus { };

std::array<int, 12> GLFWInputManager::s_mouseButtonPressed { };
std::array<Action, 12> GLFWInputManager::s_mouseButtonStatus { };

Maths::Vector2 GLFWInputManager::s_mouseScroll { };
Maths::Vector2 GLFWInputManager::s_currentMousePos { };
Maths::Vector2 GLFWInputManager::s_previousMousePos { };


int GLFWInputManager::IsKeyDown(const Key& a_key)
{
    const int l_keyInt = static_cast<int>(a_key);
    return s_keyStatus[l_keyInt] == Action::PRESS || s_keyStatus[l_keyInt] == Action::REPEAT;
}


int GLFWInputManager::IsKeyReleased(const Key& a_key)
{
    const int l_keyInt = static_cast<int>(a_key);
    return s_keyStatus[l_keyInt] == Action::RELEASE;
}


int GLFWInputManager::IsKeyPressed(const Key& a_key)
{
    const int l_keyInt = static_cast<int>(a_key);
    if (s_keyPressed[l_keyInt] == 0)
    {
        if (s_keyStatus[l_keyInt] == Action::PRESS)
        {
            s_keyPressed[l_keyInt] = 1;
            return s_keyStatus[l_keyInt] == Action::PRESS;
        }
        return false;
    }
    return false;
}


void GLFWInputManager::ConfigureMouseInput(const CursorInputMode& a_cursorInputMode)
{
    glfwSetInputMode(m_window, GLFW_CURSOR, CastGlfwInput(a_cursorInputMode));
}


void GLFWInputManager::KeyCallback(GLFWwindow* a_window, const int a_key, int a_scancode, int a_action, int a_mods)
{
    const auto l_keyAction = static_cast<Action>(a_action);
    if (l_keyAction == Action::RELEASE)
        s_keyPressed[a_key] = 0;

    s_keyStatus[a_key] = l_keyAction;
}


int GLFWInputManager::IsMouseButtonReleased(const MouseButton& a_button)
{
    const int l_buttonInt = static_cast<int>(a_button);
    return s_mouseButtonStatus[l_buttonInt] == Action::RELEASE;
}


int GLFWInputManager::IsMouseButtonDown(const MouseButton& a_button)
{
    const int l_buttonInt = static_cast<int>(a_button);
    return s_mouseButtonStatus[l_buttonInt] == Action::PRESS || s_mouseButtonStatus[l_buttonInt] == Action::REPEAT;
}


int GLFWInputManager::IsMouseButtonPressed(const MouseButton& a_button)
{
    const int l_buttonInt = static_cast<int>(a_button);
    if (s_mouseButtonPressed[l_buttonInt] == 0)
    {
        if (s_mouseButtonStatus[l_buttonInt] == Action::PRESS)
        {
            s_mouseButtonPressed[l_buttonInt] = 1;
            return s_mouseButtonStatus[l_buttonInt] == Action::PRESS;
        }
        return false;
    }
    return false;
}


void GLFWInputManager::MouseButtonCallback(GLFWwindow* a_window, const int a_button, int a_action, int a_mods)
{
    const auto l_buttonAction = static_cast<Action>(a_action);
    if (l_buttonAction == Action::RELEASE)
        s_mouseButtonPressed[a_button] = 0;

    s_mouseButtonStatus[a_button] = l_buttonAction;
}


void GLFWInputManager::MouseScrollCallback(GLFWwindow* a_window, const double a_xOffset, const double a_yOffset)
{
    SetMouseScrollCallback(a_xOffset, a_yOffset);
}

void GLFWInputManager::MouseCursorCallback(GLFWwindow* a_window, const double a_xPos, const double a_yPos)
{
    SetCursorPositionCallback(a_xPos, a_yPos);
}


void GLFWInputManager::Initialize(IWindow* a_window)
{
    m_window = a_window->CastGLFW()->GetGLFWWindow();

    glfwSetKeyCallback(m_window, KeyCallback);
    glfwSetMouseButtonCallback(m_window, MouseButtonCallback);
    glfwSetScrollCallback(m_window, MouseScrollCallback);
    glfwSetCursorPosCallback(m_window, MouseCursorCallback);
}


void GLFWInputManager::Destroy(IWindow* a_window)
{
    glfwDestroyWindow(a_window->CastGLFW()->GetGLFWWindow());
    glfwTerminate();
}