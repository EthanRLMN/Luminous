#pragma once

#include "IBuffer.hpp"
#include "ICommandBuffer.hpp"
#include "ICommandPool.hpp"
#include "IDepthResource.hpp"
#include "IDescriptor.hpp"
#include "IDescriptorSetLayout.hpp"
#include "IDevice.hpp"
#include "IFrameBuffer.hpp"
#include "IInputManager.hpp"
#include "IInstance.hpp"
#include "IMesh.hpp"
#include "IPipeline.hpp"
#include "IRenderer.hpp"
#include "IRenderPass.hpp"
#include "ISurface.hpp"
#include "ISwapChain.hpp"
#include "ISynchronization.hpp"
#include "ITexture.hpp"
#include "IWindow.hpp"
#include "ResourceManager/ResourceManager.hpp"


class IRender
{
public:
	virtual ~IRender() = default;

	virtual IWindow* InstantiateWindow() = 0;
	virtual IInputManager* InstantiateInputManager() = 0;

	virtual IInstance* InstantiateContext() = 0;
	virtual ISurface* InstantiateSurface() = 0;
	virtual IDevice* InstantiateDevice() = 0;
	virtual ISwapChain* InstantiateSwapChain() = 0;
	virtual IRenderPass* InstantiateRenderPass() = 0;
	virtual IDescriptorSetLayout* InstantiateDescriptorSetLayout() = 0;
	virtual IPipeline* InstantiatePipeline() = 0;
	virtual ICommandPool* InstantiateCommandPool() = 0;
	virtual IDepthResource* InstantiateDepthResource() = 0;
	virtual IFrameBuffer* InstantiateFrameBuffer() = 0;
	virtual ITexture* InstantiateTexture() = 0;
	virtual IMesh* InstantiateModel() = 0;
	virtual IBuffer* InstantiateBuffer() = 0;
	virtual IDescriptor* InstantiateDescriptor() = 0;
	virtual ICommandBuffer* InstantiateCommandBuffer() = 0;
	virtual ISynchronization* InstantiateSynchronization() = 0;
	virtual IResourceManager* InstantiateResourceManager() = 0;
	virtual IRenderer* InstantiateRenderingDraw() = 0;


	virtual void DeleteWindow(IWindow* a_window) { delete a_window; }
	virtual void DeleteInputManager(IInputManager* a_inputManager) { delete a_inputManager; }

	virtual void DeleteContext(IInstance* a_instance) { delete a_instance; }
	virtual void DeleteSurface(ISurface* a_surface) { delete a_surface; }
	virtual void DeleteDevice(IDevice* a_device) { delete a_device; }
	virtual void DeleteSwapChain(ISwapChain* a_swapChain) { delete a_swapChain; }
	virtual void DeleteRenderPass(IRenderPass* a_renderPass) { delete a_renderPass; }
	virtual void DeleteDescriptorSetLayout(IDescriptorSetLayout* a_descriptorSetLayout) { delete a_descriptorSetLayout; }
	virtual void DeletePipeline(IPipeline* a_pipeline) { delete a_pipeline; }
	virtual void DeleteCommandPool(ICommandPool* a_commandPool) { delete a_commandPool; }
	virtual void DeleteDepthResource(IDepthResource* a_depthResource) { delete a_depthResource; }
	virtual void DeleteFrameBuffer(IFrameBuffer* a_frameBuffer) { delete a_frameBuffer; }
	virtual void DeleteTexture(ITexture* a_texture) { delete a_texture; }
	virtual void DeleteModel(IMesh* a_mesh) { delete a_mesh; }
	virtual void DeleteBuffer(IBuffer* a_buffer) { delete a_buffer; }
	virtual void DeleteDescriptor(IDescriptor* a_descriptor) { delete a_descriptor; }
	virtual void DeleteCommandBuffer(ICommandBuffer* a_commandBuffer) { delete a_commandBuffer; }
	virtual void DeleteSynchronization(ISynchronization* a_synchronization) { delete a_synchronization; }
	virtual void DeleteResourceManager(IResourceManager* a_resourceManager) { delete a_resourceManager; }
	virtual void DeleteRenderingDraw(IRenderer* a_renderingDraw) { delete a_renderingDraw; }
};
