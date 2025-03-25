#pragma once
#include "Logger.hpp"

class VulkanRenderingDraw;
class IDevice;
class IWindow;
class ISwapChain;
class IPipeline;
class IBuffer;
class IRenderPass;
class IDescriptor;

class IRenderingDraw
{
public:
	virtual void Create(GLFWwindow* a_window, IDevice* a_device, ISwapChain* a_swapChain, IPipeline* a_pipeline, IBuffer* a_buffer, IRenderPass* a_renderPass, IDescriptor* a_descriptor) = 0;
	virtual void Destroy() = 0;


	virtual VulkanRenderingDraw* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan Draw : Cast is Wrong!\n");
		return nullptr;
	}
};
