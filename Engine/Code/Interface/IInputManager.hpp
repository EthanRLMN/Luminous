#pragma once

#include "Utils/Exporter.hpp"

#include <iostream>

class GLFWInputManager;
class IWindow;

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

	virtual IInputManager* CastGLFW()
	{
		std::cout << "Wrong cast\n";
		return nullptr;
	}
private:
};

