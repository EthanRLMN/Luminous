#pragma once

#include "IBuffer.hpp"
#include "IDevice.hpp"
#include "IInputManager.hpp"
#include "IInstance.hpp"
#include "IPipeline.hpp"
#include "IRenderPass.hpp"
#include "ISurface.hpp"
#include "ISwapChain.hpp"
#include "ISynchronisation.hpp"
#include "IWindow.hpp"

class IRender
{
public:
	virtual ~IRender() = default;

	virtual IInstance* InstantiateContext() = 0;
	virtual ISurface* InstantiateSurface() = 0;
	virtual IDevice* InstantiateDevice() = 0;
	virtual ISwapChain* InstantiateSwapChain() = 0;
	virtual IRenderPass* InstantiateRenderPass() = 0;
	virtual IPipeline* InstantiatePipeline() = 0;
	virtual IBuffer* InstantiateBuffer() = 0;
	virtual ISynchronisation* InstantiateSynchronisation() = 0;
	virtual IWindow* InstantiateWindow() = 0;
	virtual IInputManager* InstantiateInputManager() = 0;

	virtual void DeleteContext(IInstance* a_instance) { delete a_instance; }
	virtual void DeleteSurface(ISurface* a_surface) { delete a_surface; }
	virtual void DeleteDevice(IDevice* a_device) { delete a_device; }
	virtual void DeleteSwapChain(ISwapChain* a_swapchain) { delete a_swapchain; }
	virtual void DeleteRenderPass(IRenderPass* a_renderpass) { delete a_renderpass; }
	virtual void DeletePipeline(IPipeline* a_pipeline) { delete a_pipeline; }
	virtual void DeleteBuffer(IBuffer* a_buffer) { delete a_buffer; }
	virtual void DeleteSynchronisation(ISynchronisation* a_synchronisation) { delete a_synchronisation; }
	virtual void DeleteWindow(IWindow* a_window) { delete a_window; }
	virtual void DeleteInputManager(IInputManager* a_inputManager) { delete a_inputManager; }
};
