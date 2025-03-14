#pragma once
#include "IInputManager.hpp"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


class LUMINOUS_ENGINE_API VulkanInputManager : public IInputManager
{
public:

    int IsKeyDown(IWindow* a_window, int a_key) override;
    int IsKeyUp(IWindow* a_window, int a_key) override;

    VulkanInputManager* CastVulkan() override { return this; }

};