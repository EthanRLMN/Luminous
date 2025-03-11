#pragma once

#include <iostream>
#include <set>
#include <vulkan/vulkan.h>

#include "IRenderPass.hpp"

class VulkanRenderPass : public IRenderPass
{
public :
    void Create(ISwapChain* a_swapchain, IDevice* a_device) override;
    void Destroy(IDevice* _device) override;

private:
    VkRenderPass renderPass = VK_NULL_HANDLE;
};
