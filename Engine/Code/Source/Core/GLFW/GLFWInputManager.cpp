#include "IWindow.hpp"

#include "Core/GLFW/GLFWInputManager.hpp"
#include "Core/GLFW/GLFWWindow.hpp"

std::array<int, 349> GLFWInputManager::m_keyPressed { };
std::array<Action, 349> GLFWInputManager::m_keyStatus { };

std::array<int, 12> GLFWInputManager::m_mouseButtonPressed { };
std::array<Action, 12> GLFWInputManager::m_mouseButtonStatus { };

Maths::Vector2 GLFWInputManager::m_mouseScroll { };
Maths::Vector2 GLFWInputManager::m_currentMousePos { };
Maths::Vector2 GLFWInputManager::m_previousMousePos { };


int GLFWInputManager::IsKeyDown(IWindow* a_window, const Key& a_key)
{
    const int l_keyInt = static_cast<int>(a_key);
    return m_keyStatus[l_keyInt] == Action::PRESS || m_keyStatus[l_keyInt] == Action::REPEAT;
}


int GLFWInputManager::IsKeyUp(IWindow* a_window, const Key& a_key)
{
    const int l_keyInt = static_cast<int>(a_key);
    return m_keyStatus[l_keyInt] == Action::RELEASE;
}


int GLFWInputManager::IsKeyPressed(IWindow* a_window, const Key& a_key)
{
    const int l_keyInt = static_cast<int>(a_key);
    if (m_keyPressed[l_keyInt] == 0)
    {
        if (m_keyStatus[l_keyInt] == Action::PRESS)
        {
            m_keyPressed[l_keyInt] = 1;
            return m_keyStatus[l_keyInt] == Action::PRESS;
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
        m_keyPressed[a_key] = 0;

    m_keyStatus[a_key] = l_keyAction;
}


int GLFWInputManager::IsMouseButtonUp(IWindow* a_window, const MouseButton& a_button)
{
    const int l_buttonInt = static_cast<int>(a_button);
    return m_mouseButtonStatus[l_buttonInt] == Action::RELEASE;
}


int GLFWInputManager::IsMouseButtonDown(IWindow* a_window, const MouseButton& a_button)
{
    const int l_buttonInt = static_cast<int>(a_button);
    return m_mouseButtonStatus[l_buttonInt] == Action::PRESS || m_mouseButtonStatus[l_buttonInt] == Action::REPEAT;
}


int GLFWInputManager::IsMouseButtonPressed(IWindow* a_window, const MouseButton& a_button)
{
    const int l_buttonInt = static_cast<int>(a_button);
    if (m_mouseButtonPressed[l_buttonInt] == 0)
    {
        if (m_mouseButtonStatus[l_buttonInt] == Action::PRESS)
        {
            m_mouseButtonPressed[l_buttonInt] = 1;
            return m_mouseButtonStatus[l_buttonInt] == Action::PRESS;
        }
        return false;
    }
    return false;
}


void GLFWInputManager::MouseButtonCallback(GLFWwindow* a_window, const int a_button, int a_action, int a_mods)
{
    const auto l_buttonAction = static_cast<Action>(a_action);
    if (l_buttonAction == Action::RELEASE)
        m_mouseButtonPressed[a_button] = 0;

    m_mouseButtonStatus[a_button] = l_buttonAction;
}


void GLFWInputManager::MouseScrollCallback(GLFWwindow* a_window, const double a_xOffset, const double a_yOffset)
{
    SetMouseScroll(a_xOffset, a_yOffset);
    DEBUG_LOG_WARNING("Mouse Scroll : {}, {}\n", a_xOffset, a_yOffset);
}

void GLFWInputManager::MouseCursorCallback(GLFWwindow* a_window, const double a_xPos, const double a_yPos)
{
    SetCursorPosition(a_xPos, a_yPos);
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