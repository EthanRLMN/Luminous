#include "IWindow.hpp"

#include "Core/GLFW/GLFWInputManager.hpp"

#include <ranges>

#include "Core/GLFW/GLFWWindow.hpp"
#include "Game/Systems/Input/InputAction.hpp"


void GLFWInputManager::Initialize(IWindow* a_window)
{
    m_window = a_window->CastGLFW();

    glfwSetWindowUserPointer(m_window->GetGLFWWindow(), this);

    glfwSetKeyCallback(m_window->GetGLFWWindow(), KeyCallback);
    glfwSetMouseButtonCallback(m_window->GetGLFWWindow(), MouseButtonCallback);
    glfwSetScrollCallback(m_window->GetGLFWWindow(), MouseScrollCallback);
    glfwSetCursorPosCallback(m_window->GetGLFWWindow(), MouseCursorCallback);
}


void GLFWInputManager::Update()
{
    for (auto& l_action : m_actions | std::views::values)
    {
        l_action.m_isPressed = false;
        l_action.m_isDown = false;
        l_action.m_isReleased = false;

        for (const auto& [l_key, l_mods] : l_action.m_bindings)
        {
            if (IsKeyPressed(l_key) && m_currentMods == l_mods)
                l_action.m_isPressed = true;
            if (IsKeyDown(l_key) && m_currentMods == l_mods)
                l_action.m_isDown = true;
            if (IsKeyReleased(l_key) && m_currentMods == l_mods)
                l_action.m_isReleased = true;
        }
    }

    m_keyPressed.fill(0);
    m_mouseButtonPressed.fill(0);
}


int GLFWInputManager::CastGlfwInput(const CursorInputMode& a_cursorInputMode)
{
    const int l_cursorInputIndex = static_cast<int>(a_cursorInputMode);
    return glfwCursorInputType[l_cursorInputIndex];
}


int GLFWInputManager::IsKeyDown(const Key& a_key) const
{
    if (!IsKeyValid(a_key))
        return false;

    const int l_keyInt = ToIndex(a_key);
    return m_keyStatus[l_keyInt] == Action::PRESS || m_keyStatus[l_keyInt] == Action::REPEAT;
}


int GLFWInputManager::IsKeyReleased(const Key& a_key) const
{
    if (!IsKeyValid(a_key))
        return false;

    const int l_keyInt = ToIndex(a_key);
    return m_keyStatus[l_keyInt] == Action::RELEASE;
}


int GLFWInputManager::IsKeyPressed(const Key& a_key)
{
    if (!IsKeyValid(a_key))
        return false;

    const int l_keyIndex = ToIndex(a_key);
    if (m_keyPressed[l_keyIndex] == 0 && m_keyStatus[l_keyIndex] == Action::PRESS)
    {
        m_keyPressed[l_keyIndex] = 1;
        return true;
    }
    return false;
}


bool GLFWInputManager::IsShortcutPressed(const Key& a_key, const int a_requiredMods, const bool a_allowRepeat)
{
    const int l_keyIndex = ToIndex(a_key);
    const bool l_isKeyDown = m_keyStatus[l_keyIndex] == Action::PRESS || (a_allowRepeat && m_keyStatus[l_keyIndex] == Action::REPEAT);
    return l_isKeyDown && (m_currentMods & a_requiredMods) == a_requiredMods;
}


bool GLFWInputManager::IsActionPressed(const std::string& a_actionName) const
{
    const auto l_it = m_actions.find(a_actionName);
    return l_it != m_actions.end() && l_it->second.m_isPressed;
}


bool GLFWInputManager::IsActionDown(const std::string& a_actionName) const
{
    const auto l_it = m_actions.find(a_actionName);
    return l_it != m_actions.end() && l_it->second.m_isDown;
}


bool GLFWInputManager::IsActionReleased(const std::string& a_actionName) const
{
    const auto l_it = m_actions.find(a_actionName);
    return l_it != m_actions.end() && l_it->second.m_isReleased;
}


void GLFWInputManager::OnKey(const int a_key, const int a_scancode, const int a_action, const int a_mods)
{
    if (!IsKeyValid(a_key))
        return;

    static_cast<void>(a_scancode); // Unused variable, cast to void to avoid warnings
    m_currentMods = a_mods;

    const auto l_keyAction = static_cast<Action>(a_action);
    if (l_keyAction == Action::RELEASE)
        m_keyPressed[a_key] = 0;

    m_keyStatus[a_key] = l_keyAction;
}


void GLFWInputManager::CreateAction(const std::string& a_actionName)
{
    if (!m_actions.contains(a_actionName))
        m_actions[a_actionName] = InputAction(a_actionName);
}


void GLFWInputManager::AddBinding(const std::string& a_actionName, const Key a_key, const int a_mods)
{
    m_actions[a_actionName].m_bindings.push_back(KeyBinding(a_key, a_mods));
}

void GLFWInputManager::UnbindAction(const std::string& a_actionName, const Key a_key, const int a_mods)
{
    const auto l_it = m_actions.find(a_actionName);
    if (l_it != m_actions.end())
    {
        std::vector<KeyBinding>& l_bindings = l_it->second.m_bindings;
        std::erase_if(l_bindings, [&](const KeyBinding& binding) { return binding.m_key == a_key && binding.m_mods == a_mods; });
    }
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
    const int l_buttonInt = ToIndex(a_button);
    return m_mouseButtonStatus[l_buttonInt] == Action::RELEASE;
}


int GLFWInputManager::IsMouseButtonDown(const MouseButton& a_button)
{
    const int l_buttonInt = ToIndex(a_button);
    return m_mouseButtonStatus[l_buttonInt] == Action::PRESS || m_mouseButtonStatus[l_buttonInt] == Action::REPEAT;
}


int GLFWInputManager::IsMouseButtonPressed(const MouseButton& a_button)
{
    const int l_buttonIndex = ToIndex(a_button);
    if (m_mouseButtonPressed[l_buttonIndex] == 0 && m_mouseButtonStatus[l_buttonIndex] == Action::PRESS)
    {
        m_mouseButtonPressed[l_buttonIndex] = 1;
        return true;
    }
    return false;
}


void GLFWInputManager::OnMouseButton(const int a_button, const int a_action, const int a_mods)
{
    static_cast<void>(a_mods); // Unused variable, cast to void to avoid warnings

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
    OnScrollUpdate(a_xOffset, a_yOffset);
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
    OnCursorPositionUpdate(a_xPos, a_yPos);
}


void GLFWInputManager::MouseCursorCallback(GLFWwindow* a_window, const double a_xPos, const double a_yPos)
{
    GLFWInputManager* l_inputManager = static_cast<GLFWInputManager*>(glfwGetWindowUserPointer(a_window));
    if (!l_inputManager)
        return;

    l_inputManager->OnCursorPos(a_xPos, a_yPos);
}