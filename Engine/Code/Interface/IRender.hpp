#pragma once

#include "IWindow.hpp"
#include "IInstance.hpp"
#include "ISurface.hpp"
#include "IDevice.hpp"
#include "ISwapChain.hpp"
#include "IRenderPass.hpp"
#include "IDescriptions.hpp"
#include "IPipeline.hpp"
#include "ICommandPool.hpp"
#include "IDepthRessource.hpp"
#include "IFrameBuffer.hpp"
#include "ITexture.hpp"
#include "IBuffer.hpp"
#include "IInputManager.hpp"
#include "ISynchronisation.hpp"

class IRender
{
public:
	virtual ~IRender() = default;

	virtual IInstance* InstantiateContext() = 0;
	virtual ISurface* InstantiateSurface() = 0;
	virtual IDevice* InstantiateDevice() = 0;
	virtual ISwapChain* InstantiateSwapChain() = 0;
	virtual IRenderPass* InstantiateRenderPass() = 0;
	virtual IDescriptor* InstantiateDescriptor() = 0;
	virtual IPipeline* InstantiatePipeline() = 0;
	virtual ICommandPool* InstantiateCommandPool() = 0;
	virtual IDepthRessource* InstantiateDepthRessource() = 0;
	virtual IFrameBuffer* InstantiateFrameBuffer() = 0;
	virtual ITexture* InstantiateTexture() = 0;
	//loadmodel
	virtual IBuffer* InstantiateBuffer() = 0;
	//descriptor
	virtual ISynchronisation* InstantiateSynchronisation() = 0;
	virtual IWindow* InstantiateWindow() = 0;
	virtual IInputManager* InstantiateInputManager() = 0;

	virtual void DeleteContext(IInstance* a_instance) { delete a_instance; }
	virtual void DeleteSurface(ISurface* a_surface) { delete a_surface; }
	virtual void DeleteDevice(IDevice* a_device) { delete a_device; }
	virtual void DeleteSwapChain(ISwapChain* a_swapchain) { delete a_swapchain; }
	virtual void DeleteRenderPass(IRenderPass* a_renderpass) { delete a_renderpass; }
	virtual void DeleteDescriptor(IDescriptor* a_descriptor) { delete a_descriptor; }
	virtual void DeletePipeline(IPipeline* a_pipeline) { delete a_pipeline; }
	virtual void DeleteCommandPool(ICommandPool* a_commandPool) { delete a_commandPool; }
	virtual void DeleteDepthRessource(IDepthRessource* a_depthRessource) { delete a_depthRessource; }
	virtual void DeleteFrameBuffer(IFrameBuffer* a_frameBuffer) { delete a_frameBuffer; }
	virtual void DeleteTexture(ITexture* a_texture) { delete a_texture; }
	virtual void DeleteBuffer(IBuffer* a_buffer) { delete a_buffer; }
	virtual void DeleteSynchronisation(ISynchronisation* a_synchronisation) { delete a_synchronisation; }
	virtual void DeleteWindow(IWindow* a_window) { delete a_window; }
	virtual void DeleteInputManager(IInputManager* a_inputManager) { delete a_inputManager; }
};
