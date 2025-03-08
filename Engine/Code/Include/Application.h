#pragma once
#include <iostream>
#include "Rendering/Window.h"


class Application {
public:
	Application();
	~Application();
	void Run();
	static void DebugInput(GLFWwindow* window, int _key, int _scancode, int _action, int _mods);

private:
	Window s_Window;
	
};