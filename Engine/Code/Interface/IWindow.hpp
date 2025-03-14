#pragma once

#include <iostream>
#include <string>

#include "Logger.hpp"

class VulkanWindow;

class Vector2 { public:Vector2() = default; Vector2(float ax, float ay) { x = ax; y = ay; }; float x = 0, y = 0; };

class IWindow
{
public:
	virtual ~IWindow() = default;

	virtual void Initialize(const std::string& a_name, int a_width, int a_height) = 0;
	virtual void Update() const = 0;
	virtual void PollEvents() const = 0;
	virtual bool ShouldClose() const = 0;
	virtual void Destroy() const = 0;

	virtual Vector2 GetSize() = 0;
	virtual void SetSize(const Vector2 a_size) = 0;
	virtual float GetOpacity() = 0;
	virtual void SetOpacity(const float a_alpha) = 0;
	virtual const std::string GetTitle() = 0;
	virtual void SetTitle(const std::string& a_name) = 0;

	virtual VulkanWindow* CastVulkan()
	{
		DEBUG_LOG_INFO("Wrong Cast\n");
		return nullptr;
	}
};
