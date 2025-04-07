#pragma once

class Engine;
class GLFWWindow;

class ImguiWindow
{
public:
	ImguiWindow() = default;
	~ImguiWindow() = default;

	void Create(const GLFWWindow* a_glfwWindow);
	void Shutdown();

	void BeginRender();
	void EndRender(const Engine* a_engine);

    bool WantCaptureMouse();
    bool WantCaptureKeyboard();
};
