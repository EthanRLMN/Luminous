#pragma once

#include <iostream>
#include <string>

#include "Exporter.hpp"

class VulkanWindow;

class IWindow
{
public:
	virtual ~IWindow() = default;

	virtual void Initialize(const std::string& a_name, int a_width, int a_height) = 0;
	virtual void Update() const = 0;
	virtual void Destroy() const = 0;

	virtual VulkanWindow* CastVulkan()
	{
		std::cout << "Wrong cast\n";
		return nullptr;
	}
};
