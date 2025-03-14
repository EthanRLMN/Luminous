#pragma once
/*
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "Exporter.hpp"

class Vector2 { public:Vector2() = default;Vector2(float ax, float ay) { x = ax; y = ay; }; float x = 0, y = 0; };

class VulkanWindow;

class LUMINOUS_ENGINE_API EWindow
{
public:
	EWindow() = default;
	EWindow(const int a_width, const int a_height, const char* a_title);
	virtual ~EWindow();
	virtual void Update();
	virtual void Close();

	virtual int WindowShouldClose();
	virtual void SetWindowShouldClose(int a_value);
	virtual Vector2 GetSize();
	virtual void SetSize(const Vector2 a_size);
	virtual float GetOpacity();
	virtual void SetOpacity(const float a_alpha);

	virtual VulkanWindow* CastToVulkan();

private:
	GLFWwindow* m_window;
};*/
