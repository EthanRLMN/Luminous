#pragma once

#include <string>

#include "Vector2.hpp"
#include "Logger.hpp"
#include "GLFW/glfw3.h"

class VulkanWindow;

class IWindow
{
public:
	virtual ~IWindow() = default;

	virtual GLFWwindow* Initialize(const std::string& a_name, int a_width, int a_height) = 0;
	virtual void Update() const = 0;
	virtual void PollEvents() const = 0;
	virtual bool ShouldClose() const = 0;
	virtual void Destroy() const = 0;

	virtual Maths::Vector2 GetSize() = 0;
	virtual void SetSize(Maths::Vector2 a_size) = 0;
	virtual float GetOpacity() = 0;
	virtual void SetOpacity(float a_alpha) = 0;
	virtual const std::string GetTitle() = 0;
	virtual void SetTitle(const std::string& a_name) = 0;

	virtual VulkanWindow* CastVulkan()
	{
		DEBUG_LOG_INFO("Wrong Cast\n");
		return nullptr;
	}
};
