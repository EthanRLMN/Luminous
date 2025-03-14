#pragma once

#include <iostream>
#include <string>

#include "Rendering/API/Vulkan/VulkanWindow.hpp"
#include <unordered_map>
#include "../Interface/IKeyCode.hpp"

class VulkanInputManager;


class LUMINOUS_ENGINE_API IInputManager
{
public:
	virtual ~IInputManager() = default;
	virtual void Initialize(IWindow* a_window) = 0;

	virtual int IsKeyDown(IWindow* a_window, int a_key) = 0;
	virtual int IsKeyUp(IWindow* a_window, int a_key) = 0;
	virtual int IsKeyPressed(IWindow* a_window, int a_key) = 0;

	virtual int IsMouseButtonDown(IWindow* a_window, int a_button) = 0;
	virtual int IsMouseButtonUp(IWindow* a_window, int a_button) = 0;
	virtual int IsMouseButtonPressed(IWindow* a_window, int a_button) = 0;

	virtual Vector2 GetCursorPosition(IWindow* a_window) = 0;
	virtual void SetCursorPosition(IWindow* a_window, Vector2 a_pos) = 0;

	virtual VulkanInputManager* CastVulkan()
	{
		std::cout << "Wrong cast\n";
		return nullptr;
	}

	IKeycode KeyCode() { return m_keycode; };

private:
	IKeycode m_keycode;
};

