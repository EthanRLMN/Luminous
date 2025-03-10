#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <stdexcept> //error checker


#include "../../LantualInstance.h"
#include "../../Window.hpp"
#include "LantualVkValidation.h"

#define DEBUG

class Window;

class LantualVKInstance : public LantualInstance
{
public :
	LantualVKInstance() = default;
	~LantualVKInstance() = default;


	void Create(Window* _window) override;
	void Destroy() override;

	VkInstance GetInstance() const override
	{
		return instance;
	}

	LantualInstance* CastVulkan() override { return this; }

private:
	VkInstance instance = VK_NULL_HANDLE;
	VkDebugReportCallbackEXT callback = VK_NULL_HANDLE;

private : 
	void VkCreateInstance();
	void VkDebugCallback();
};

