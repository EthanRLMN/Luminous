#pragma once

#include <iostream>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Exporter.hpp"

class LUMINOUS_ENGINE_API Window
{
public:
	void Initialize(const std::string& a_name, int a_width, int a_height);
	void Update() const;
	void Shutdown() const;
	void InputManager(GLFWkeyfun _input) const;

	GLFWwindow* m_Window;
};
