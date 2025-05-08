#pragma once

#include "Logger.hpp"

class IMultiSampling;
class VulkanRenderer;
class IDevice;
class IWindow;
class ISwapChain;
class IPipeline;
class IBuffer;
class IRenderPassManager;
class IRenderPass;
class IDescriptor;
class IMesh;
class ISynchronization;
class ICommandBuffer;
class IFrameBufferManager;
class ISurface;
class IDepthResource;
class IInputManager;
class EntityManager;
class ITexture;

class IRenderer
{
public:
	virtual ~IRenderer() = default;
    virtual void Create(ISwapChain* a_swapChain) = 0;
    virtual void DrawFrame(IWindow* a_window, IDevice* a_device, ISwapChain* a_swapChain, IPipeline* a_pipeline, IBuffer* a_buffer, IRenderPassManager* a_renderPassManager, IDescriptor* a_descriptor, ISynchronization* a_synchronization, ICommandBuffer* a_commandBuffer, IFrameBufferManager* a_frameBufferManager, IDepthResource* a_depthResource, ISurface* a_surface, IMultiSampling* a_multisampling, IInputManager* a_inputManager, EntityManager a_manager) = 0;
    virtual void Destroy() = 0;

	virtual VulkanRenderer* CastVulkan()
	{
		DEBUG_LOG_ERROR("Vulkan Draw : Cast is Wrong!\n");
		return nullptr;
	}
};

