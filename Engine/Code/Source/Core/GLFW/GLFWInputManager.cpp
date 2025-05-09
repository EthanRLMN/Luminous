#include "IWindow.hpp"

#include "Core/GLFW/GLFWInputManager.hpp"
#include "Core/GLFW/GLFWWindow.hpp"


void GLFWInputManager::Initialize(IWindow* a_window)
{
    m_window = a_window->CastGLFW();

    glfwSetWindowUserPointer(m_window->GetGLFWWindow(), this);

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
    m_keyPressed.fill(0);
    m_mouseButtonPressed.fill(0);
}


int GLFWInputManager::CastGlfwInput(const CursorInputMode& a_cursorInputMode)
{
    const int l_cursorInputIndex = static_cast<int>(a_cursorInputMode);
    return glfwCursorInputType[l_cursorInputIndex];
}


int GLFWInputManager::IsKeyDown(const Key& a_key)
{
    if (!IsKeyValid(a_key))
        return false;

    const int l_keyInt = static_cast<int>(a_key);
    return m_keyStatus[l_keyInt] == Action::PRESS || m_keyStatus[l_keyInt] == Action::REPEAT;
}


int GLFWInputManager::IsKeyReleased(const Key& a_key)
{
    if (!IsKeyValid(a_key))
        return false;

    const int l_keyInt = static_cast<int>(a_key);
    return m_keyStatus[l_keyInt] == Action::RELEASE;
}


int GLFWInputManager::IsKeyPressed(const Key& a_key)
{
    if (!IsKeyValid(a_key))
        return false;

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


void GLFWInputManager::OnKey(const int a_key, const int a_scancode, const int a_action, const int a_mods)
{
    if (!IsKeyValid(a_key))
        return;

    static_cast<void>(a_scancode); static_cast<void>(a_mods);

    const auto l_keyAction = static_cast<Action>(a_action);
    if (l_keyAction == Action::RELEASE)
        m_keyPressed[a_key] = 0;

    m_keyStatus[a_key] = l_keyAction;
}


void GLFWInputManager::KeyCallback(GLFWwindow* a_window, const int a_key, int a_scancode, int a_action, int a_mods)
{
    GLFWInputManager* l_inputManager = static_cast<GLFWInputManager*>(glfwGetWindowUserPointer(a_window));
    if (!l_inputManager)
        return;

    l_inputManager->OnKey(a_key, a_scancode, a_action, a_mods);
}


int GLFWInputManager::IsMouseButtonReleased(const MouseButton& a_button)
{
    const int l_buttonInt = static_cast<int>(a_button);
    return m_mouseButtonStatus[l_buttonInt] == Action::RELEASE;
}


int GLFWInputManager::IsMouseButtonDown(const MouseButton& a_button)
{
    const int l_buttonInt = static_cast<int>(a_button);
    return m_mouseButtonStatus[l_buttonInt] == Action::PRESS || m_mouseButtonStatus[l_buttonInt] == Action::REPEAT;
}


int GLFWInputManager::IsMouseButtonPressed(const MouseButton& a_button)
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


void GLFWInputManager::OnMouseButton(const int a_button, const int a_action, const int a_mods)
{
    static_cast<void>(a_mods);

    const auto l_buttonAction = static_cast<Action>(a_action);
    if (l_buttonAction == Action::RELEASE)
        m_mouseButtonPressed[a_button] = 0;

    m_mouseButtonStatus[a_button] = l_buttonAction;
}


void GLFWInputManager::MouseButtonCallback(GLFWwindow* a_window, const int a_button, int a_action, int a_mods)
{
    GLFWInputManager* l_inputManager = static_cast<GLFWInputManager*>(glfwGetWindowUserPointer(a_window));
    if (!l_inputManager)
        return;

    l_inputManager->OnMouseButton(a_button, a_action, a_mods);
}


void GLFWInputManager::OnScroll(const double a_xOffset, const double a_yOffset)
{
    SetMouseScrollCallback(a_xOffset, a_yOffset);
}


void GLFWInputManager::MouseScrollCallback(GLFWwindow* a_window, const double a_xOffset, const double a_yOffset)
{
    GLFWInputManager* l_inputManager = static_cast<GLFWInputManager*>(glfwGetWindowUserPointer(a_window));
    if (!l_inputManager)
        return;

    l_inputManager->OnScroll(a_xOffset, a_yOffset);
}


void GLFWInputManager::OnCursorPos(const double a_xPos, const double a_yPos)
{
    SetCursorPositionCallback(a_xPos, a_yPos);
}


void GLFWInputManager::MouseCursorCallback(GLFWwindow* a_window, const double a_xPos, const double a_yPos)
{
    GLFWInputManager* l_inputManager = static_cast<GLFWInputManager*>(glfwGetWindowUserPointer(a_window));
    if (!l_inputManager)
        return;

    l_inputManager->OnCursorPos(a_xPos, a_yPos);
}