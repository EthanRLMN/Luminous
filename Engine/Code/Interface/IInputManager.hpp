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

	virtual int IsKeyDown(IWindow* a_window, int a_key) = 0;
	virtual int IsKeyUp(IWindow* a_window, int a_key) = 0;

	virtual VulkanInputManager* CastVulkan()
	{
		std::cout << "Wrong cast\n";
		return nullptr;
	}

	IKeycode KeyCode() { return m_keycode; };

private:
	IKeycode m_keycode;
};

