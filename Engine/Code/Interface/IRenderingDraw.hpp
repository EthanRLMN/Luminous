#pragma once

#include "Logger.hpp"
#include "GLFW/glfw3.h"

class VulkanRenderingDraw;
class IDevice;
class IWindow;
class ISwapChain;
class IPipeline;
class IBuffer;
class IRenderPass;
class IDescriptor;
class IModel;
class ISynchronization;
class ICommandBuffer;
class IFrameBuffer;
class ISurface;
class IDepthResource;

class IRenderingDraw
{
public:
	virtual ~IRenderingDraw() = default;
	virtual void Create(IWindow* a_window, IDevice* a_device, ISwapChain* a_swapChain, IPipeline* a_pipeline, IBuffer* a_buffer, IRenderPass* a_renderPass, IDescriptor* a_descriptor, IModel* a_model, ISynchronization* a_synchronization, ICommandBuffer* a_commandBuffer, IFrameBuffer* a_frameBuffer, IDepthResource* a_depthResource, ISurface* a_surface) = 0;
	virtual void Destroy() = 0;

	virtual VulkanRenderingDraw* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan Draw : Cast is Wrong!\n");
		return nullptr;
	}
};

