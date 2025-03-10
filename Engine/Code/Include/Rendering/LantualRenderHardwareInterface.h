#pragma once
#include <iostream>
#include "LantualRender.h"

#include "API/Vulkan/LantualVKInstance.h"
#include "API/Vulkan/LantualVKSurface.h"
#include "API/Vulkan/LantualVkDevice.h"
#include "API/Vulkan/LantualVkSwapChain.h"
#include "API/Vulkan/LantualVkRenderPass.h"
#include "API/Vulkan/LantualVkPipeline.h"
#include "API/Vulkan/LantualVkBuffer.h"
#include "API/Vulkan/LantualVkSynchronisation.h"

#define VULKAN



class LantualRenderHardwareInterface : public LantualRender
{

public:
	
#ifdef VULKAN
	LantualInstance* InstantiateContext() override { return new LantualVKInstance(); }
	virtual void DeleteContext(LantualInstance* _instance) { delete _instance; };

	LantualSurface* InstantiateSurface() override { return new LantualVkSurface(); }
	virtual void DeleteSurface(LantualVkSurface* _surface) { delete _surface; };

	LantualDevice* InstantiateDevice() override { return new LantualVkDevice(); }
	virtual void DeleteDevice(LantualDevice* _device) { delete  _device; }

	LantualSwapChain* InstantiateSwapChain() override { return new LantualVkSwapChain(); }
	virtual void DeleteSwapChain(LantualSwapChain* _swapchain) { delete  _swapchain; }

	LantualRenderPass* InstantiateRenderPass() override { return new LantualVkRenderPass(); }
	virtual void DeleteRenderPass(LantualRenderPass* _renderpass) { delete  _renderpass; }

	LantualPipeline* InstantiatePipeline()  override{ return new LantualVkPipeline(); }
	virtual void DeletePipeline(LantualPipeline* _pipeline) { delete  _pipeline; }


	LantualBuffer* InstantiateBuffer() override { return new LantualVkBuffer(); }
	virtual void DeleteBuffer(LantualBuffer* _buffer) { delete  _buffer; }


	LantualSynchronisation* InstantiateSynchronisation() override { return new LantualVkSynchronisation; }
	virtual void DeleteSynchronisation(LantualSynchronisation* _synchronisation) { delete  _synchronisation; }

#endif // VULKAN

	


};
