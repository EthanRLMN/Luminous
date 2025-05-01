#pragma once

#include "Logger.hpp"
#include "Vector2.hpp"
#include "Utils/InputWrapperUtils.hpp"

class GLFWInputManager;
class IWindow;


enum class CursorInputMode
{
    NORMAL,
    HIDDEN,
    DISABLED,
    CAPTURED
};


class IInputManager
{
public:
	virtual ~IInputManager() = default;
	virtual void Initialize(IWindow* a_window) = 0;
	virtual void Destroy(IWindow* a_window) = 0;
	virtual void Update(IWindow* a_window) = 0;

	virtual int IsKeyDown(const Key& a_key) = 0;
	virtual int IsKeyUp(const Key& a_key) = 0;
	virtual int IsKeyPressed(const Key& a_key) = 0;

	virtual int IsMouseButtonDown(const MouseButton& a_button) = 0;
	virtual int IsMouseButtonUp(const MouseButton& a_button) = 0;
	virtual int IsMouseButtonPressed(const MouseButton& a_button) = 0;

	virtual Maths::Vector2 GetMouseScroll() = 0;
    virtual Maths::Vector2 GetCursorPosition() = 0;
    virtual Maths::Vector2 GetMouseDelta() = 0;

    virtual void ConfigureMouseInput(const CursorInputMode& a_cursorInputMode) = 0;
    virtual void ResetMouseDelta() = 0;

    virtual void SetCursorPosition(const double& a_xPos, const double& a_yPos) = 0;
    virtual void SetMouseScroll(const double& a_xAxis, const double& a_yAxis) = 0;

    virtual IInputManager* CastGLFW()
	{
		DEBUG_LOG_ERROR("Input Manager : Cast is Wrong!\n");
		return nullptr;
	}
};

