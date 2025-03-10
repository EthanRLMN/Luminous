#pragma once
#include <iostream>
#include <vulkan/vulkan.h>

#include "../../LantualSurface.h"
#include "../../LantualInstance.h"
#include "../../Window.hpp"


class LantualVkSurface : public LantualSurface
{
public:
	void Create(LantualInstance* _instance, Window* _window) override;
	void Destroy(LantualInstance* _instance) override;

	virtual VkSurfaceKHR GetSurface() const
	{
		return surface;
	}

	virtual LantualSurface* CastVulkan() override { return this; }


private:
	VkSurfaceKHR surface = VK_NULL_HANDLE;
};

