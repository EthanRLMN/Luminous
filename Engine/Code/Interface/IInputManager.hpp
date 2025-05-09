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
    virtual void Update() = 0;

	[[nodiscard]] virtual int IsKeyDown(const Key& a_key) const = 0;
	[[nodiscard]] virtual int IsKeyReleased(const Key& a_key) const = 0;
	[[nodiscard]] virtual int IsKeyPressed(const Key& a_key) const = 0;

	[[nodiscard]] virtual int IsMouseButtonDown(const MouseButton& a_button) const = 0;
	[[nodiscard]] virtual int IsMouseButtonReleased(const MouseButton& a_button) const = 0;
	[[nodiscard]] virtual int IsMouseButtonPressed(const MouseButton& a_button) const = 0;

	[[nodiscard]] virtual Maths::Vector2 GetMouseScroll() const = 0;
    [[nodiscard]] virtual Maths::Vector2 GetCursorPosition() const = 0;
    [[nodiscard]] virtual Maths::Vector2 GetMouseDelta() const = 0;

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