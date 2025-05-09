#include "IWindow.hpp"

#include "Core/GLFW/GLFWInputManager.hpp"
#include "Core/GLFW/GLFWWindow.hpp"

std::array<int, LUMINOUS_KEY_LAST> GLFWInputManager::s_keyPressed{};
std::array<Action, LUMINOUS_KEY_LAST> GLFWInputManager::s_keyStatus{};

std::array<int, LUMINOUS_MOUSE_BUTTON_LAST> GLFWInputManager::s_mouseButtonPressed{};
std::array<Action, LUMINOUS_MOUSE_BUTTON_LAST> GLFWInputManager::s_mouseButtonStatus{};

Maths::Vector2 GLFWInputManager::s_mouseScroll{};
Maths::Vector2 GLFWInputManager::s_currentMousePos{};
Maths::Vector2 GLFWInputManager::s_previousMousePos{};


int GLFWInputManager::IsKeyDown(const Key& a_key) const
{
    if (!IsKeyValid(a_key))
        return false;

    const int l_keyInt = static_cast<int>(a_key);
    return s_keyStatus[l_keyInt] == Action::PRESS || s_keyStatus[l_keyInt] == Action::REPEAT;
}


int GLFWInputManager::IsKeyReleased(const Key& a_key) const
{
    if (!IsKeyValid(a_key))
        return false;

    const int l_keyInt = static_cast<int>(a_key);
    return s_keyStatus[l_keyInt] == Action::RELEASE;
}


int GLFWInputManager::IsKeyPressed(const Key& a_key) const
{
    if (!IsKeyValid(a_key))
        return false;

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


void GLFWInputManager::KeyCallback(GLFWwindow* a_window, const int a_key, int a_scancode, int a_action, int a_mods)
{
    static_cast<void>(a_window);
    static_cast<void>(a_scancode);
    static_cast<void>(a_mods);

    if (!IsKeyValid(a_key))
        return;

    const auto l_keyAction = static_cast<Action>(a_action);
    if (l_keyAction == Action::RELEASE)
        s_keyPressed[a_key] = 0;

    s_keyStatus[a_key] = l_keyAction;
}


int GLFWInputManager::IsMouseButtonReleased(const MouseButton& a_button) const
{
    const int l_buttonInt = static_cast<int>(a_button);
    return s_mouseButtonStatus[l_buttonInt] == Action::RELEASE;
}


int GLFWInputManager::IsMouseButtonDown(const MouseButton& a_button) const
{
    const int l_buttonInt = static_cast<int>(a_button);
    return s_mouseButtonStatus[l_buttonInt] == Action::PRESS || s_mouseButtonStatus[l_buttonInt] == Action::REPEAT;
}


int GLFWInputManager::IsMouseButtonPressed(const MouseButton& a_button) const
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
    static_cast<void>(a_window);
    static_cast<void>(a_mods);

    const auto l_buttonAction = static_cast<Action>(a_action);
    if (l_buttonAction == Action::RELEASE)
        s_mouseButtonPressed[a_button] = 0;

    s_mouseButtonStatus[a_button] = l_buttonAction;
}


void GLFWInputManager::MouseScrollCallback(GLFWwindow* a_window, const double a_xOffset, const double a_yOffset)
{
    static_cast<void>(a_window);
    SetMouseScrollCallback(a_xOffset, a_yOffset);
}

void GLFWInputManager::MouseCursorCallback(GLFWwindow* a_window, const double a_xPos, const double a_yPos)
{
    static_cast<void>(a_window);
    SetCursorPositionCallback(a_xPos, a_yPos);
}


int GLFWInputManager::CastGlfwInput(const CursorInputMode& a_cursorInputMode)
{
    const int l_cursorInputIndex = static_cast<int>(a_cursorInputMode);
    return glfwCursorInputType[l_cursorInputIndex];
}

void GLFWInputManager::Initialize(IWindow* a_window)
{
    m_window = a_window->CastGLFW();

    glfwSetKeyCallback(m_window->GetGLFWWindow(), KeyCallback);
    glfwSetMouseButtonCallback(m_window->GetGLFWWindow(), MouseButtonCallback);
    glfwSetScrollCallback(m_window->GetGLFWWindow(), MouseScrollCallback);
    glfwSetCursorPosCallback(m_window->GetGLFWWindow(), MouseCursorCallback);
}


void GLFWInputManager::Destroy(IWindow* a_window)
{
    glfwDestroyWindow(a_window->CastGLFW()->GetGLFWWindow());
    glfwTerminate();
}


void GLFWInputManager::Update()
{
    s_keyPressed.fill(0);
    s_mouseButtonPressed.fill(0);
}
