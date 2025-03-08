#pragma once
#define DEBUG
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>


class Window {

public:
	void Initialize(const std::string name, const int width, const int height);
	void Update();
	void Shutdown();
	void InputManager(GLFWkeyfun _input);


public:
	GLFWwindow* m_Window;

};
