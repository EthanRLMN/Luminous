#pragma once

#include "LantualInstance.h"
#include "LantualSurface.h"
#include "LantualDevice.h"
#include "LantualSwapChain.h"
#include "LantualRenderPass.h"
#include "LantualPipeline.h"
#include "LantualBuffer.h"
#include "LantualSynchronisation.h"


class LantualRender {

public:

	virtual LantualInstance* InstantiateContext() = 0;
	virtual LantualSurface* InstantiateSurface() = 0;
	virtual LantualDevice* InstantiateDevice() = 0;
	virtual LantualSwapChain* InstantiateSwapChain() = 0;
	virtual LantualRenderPass* InstantiateRenderPass() = 0;
	virtual LantualPipeline* InstantiatePipeline() = 0;
	virtual LantualBuffer* InstantiateBuffer() = 0;
	virtual LantualSynchronisation* InstantiateSynchronisation() = 0;

	
	virtual void DeleteContext(LantualInstance* _instance) { delete  _instance; }
	virtual void DeleteSurface(LantualSurface* _surface) { delete  _surface; }
	virtual void DeleteDevice(LantualDevice* _device) { delete  _device; }
	virtual void DeleteSwapChain(LantualSwapChain* _swapchain) { delete  _swapchain; }
	virtual void DeleteRenderPass(LantualRenderPass* _renderpass) { delete  _renderpass; }
	virtual void DeletePipeline(LantualPipeline* _pipeline) { delete  _pipeline; }
	virtual void DeleteBuffer(LantualBuffer* _buffer) { delete  _buffer; }
	virtual void DeleteSynchronisation(LantualSynchronisation* _synchronisation) { delete  _synchronisation; }
};
