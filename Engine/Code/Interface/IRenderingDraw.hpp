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
class IMesh;
class ISynchronization;
class ICommandBuffer;
class IFrameBuffer;
class ISurface;
class IDepthResource;

class IRenderingDraw
{
public:
	virtual ~IRenderingDraw() = default;
    virtual void Create(IWindow* a_window, IDevice* a_device, ISwapChain* a_swapChain, IPipeline* a_pipeline, IBuffer* a_buffer, IRenderPass* a_renderPass, IDescriptor* a_descriptor, IMesh* a_mesh, ISynchronization* a_synchronization, ICommandBuffer* a_commandBuffer, IFrameBuffer* a_frameBuffer, IDepthResource* a_depthResource, ISurface* a_surface) = 0;
	virtual void Destroy() = 0;

	virtual VulkanRenderingDraw* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan Draw : Cast is Wrong!\n");
		return nullptr;
	}
};

