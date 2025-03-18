#pragma once

#include "Utils/Exporter.hpp"

#include <iostream>
#include "Vector2.hpp"
#include "Utils/InputWrapperUtils.hpp"

class GLFWInputManager;
class IWindow;

class LUMINOUS_ENGINE_API IInputManager
{
public:
	virtual ~IInputManager() = default;
	virtual void Initialize(IWindow* a_window) = 0;
	virtual void Destroy(IWindow* a_window) = 0;
	virtual void Update(IWindow* a_window) = 0;

	virtual int IsKeyDown(IWindow* a_window, Key a_key) = 0;
	virtual int IsKeyUp(IWindow* a_window, Key a_key) = 0;
	virtual int IsKeyPressed(IWindow* a_window, Key a_key) = 0;

	virtual int IsMouseButtonDown(IWindow* a_window, MouseButton a_button) = 0;
	virtual int IsMouseButtonUp(IWindow* a_window, MouseButton a_button) = 0;
	virtual int IsMouseButtonPressed(IWindow* a_window, MouseButton a_button) = 0;

	virtual Maths::Vector2 GetMouseScroll() = 0;
	virtual void SetMouseScroll(Maths::Vector2 a_vec) = 0;

	virtual Maths::Vector2 GetCursorPosition(IWindow* a_window) = 0;
	virtual void SetCursorPosition(IWindow* a_window, Maths::Vector2 a_pos) = 0;

	virtual IInputManager* CastGLFW()
	{
		std::cout << "Wrong cast\n";
		return nullptr;
	}
};

