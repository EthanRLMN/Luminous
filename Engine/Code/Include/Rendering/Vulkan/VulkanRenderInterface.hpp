#pragma once

#include "IRender.hpp"

#include "Core/GLFW/GLFWInputManager.hpp"
#include "Core/GLFW/GLFWWindow.hpp"

#include "VulkanBuffer.hpp"
#include "VulkanCommandBuffer.hpp"
#include "VulkanCommandPool.hpp"
#include "VulkanDepthResource.hpp"
#include "VulkanDescriptor.hpp"
#include "VulkanDescriptorSetLayout.hpp"
#include "VulkanDevice.hpp"
#include "VulkanFrameBufferManager.hpp"
#include "VulkanInstance.hpp"
#include "VulkanMesh.hpp"
#include "VulkanMultiSampling.hpp"
#include "VulkanPipeline.hpp"
#include "VulkanRenderPassManager.hpp"
#include "VulkanRenderer.hpp"
#include "VulkanSurface.hpp"
#include "VulkanSwapChain.hpp"
#include "VulkanSynchronization.hpp"
#include "VulkanTexture.hpp"

class VulkanRenderInterface final : public IRender
{
public:
	inline IWindow* InstantiateWindow() override { return new GLFWWindow(); }
	void DeleteWindow(IWindow* a_window) override { delete a_window; }

	inline IInputManager* InstantiateInputManager() override { return new GLFWInputManager(); }
	void DeleteInputManager(IInputManager* a_inputManager) override { delete a_inputManager; }

	inline IInstance* InstantiateContext() override { return new VulkanInstance(); }
	void DeleteContext(IInstance* a_instance) override { delete a_instance; }

	inline ISurface* InstantiateSurface() override { return new VulkanSurface(); }
	void DeleteSurface(ISurface* a_surface) override { delete a_surface; }

	inline IDevice* InstantiateDevice() override { return new VulkanDevice(); }
	void DeleteDevice(IDevice* a_device) override { delete a_device; }

	inline ISwapChain* InstantiateSwapChain() override { return new VulkanSwapChain(); }
	void DeleteSwapChain(ISwapChain* a_swapChain) override { delete a_swapChain; }

	inline IRenderPassManager* InstantiateRenderPassManager() override { return new VulkanRenderPassManager(); }
	void DeleteRenderPassManager(IRenderPassManager* a_renderPassManager) override { delete a_renderPassManager; }

	inline IDescriptorSetLayout* InstantiateDescriptorSetLayout() override { return new VulkanDescriptorSetLayout(); }
	void DeleteDescriptorSetLayout(IDescriptorSetLayout* a_descriptorSetLayout) override { delete a_descriptorSetLayout; }

	inline IPipeline* InstantiatePipeline() override { return new VulkanPipeline(); }
	void DeletePipeline(IPipeline* a_pipeline) override { delete a_pipeline; }

	inline ICommandPool* InstantiateCommandPool() override { return new VulkanCommandPool(); }
	void DeleteCommandPool(ICommandPool* a_commandPool) override { delete a_commandPool; }

	inline IMultiSampling* InstantiateMultiSampling() override { return new VulkanMultiSampling(); }
    void DeleteMultiSampling(IMultiSampling* a_multiSampling) override { delete a_multiSampling; };

	inline IDepthResource* InstantiateDepthResource() override { return new VulkanDepthResource(); }
	void DeleteDepthResource(IDepthResource* a_depthResource) override { delete a_depthResource; }

	inline IFrameBufferManager* InstantiateFrameBufferManager() override { return new VulkanFrameBufferManager(); }
	void DeleteFrameBufferManager(IFrameBufferManager* a_frameBufferManager) override { delete a_frameBufferManager; }

	inline ITexture* InstantiateTexture() override { return new VulkanTexture(); }
	void DeleteTexture(ITexture* a_texture) override { delete a_texture; }

	inline IMesh* InstantiateModel() override { return new VulkanMesh(); }
	void DeleteModel(IMesh* a_mesh) override { delete a_mesh; }

	inline IBuffer* InstantiateBuffer() override { return new VulkanBuffer(); }
	void DeleteBuffer(IBuffer* a_buffer) override { delete a_buffer; }

	inline IDescriptor* InstantiateDescriptor() override { return new VulkanDescriptor(); }
	void DeleteDescriptor(IDescriptor* a_descriptor) override { delete a_descriptor; }

	inline ICommandBuffer* InstantiateCommandBuffer() override { return new VulkanCommandBuffer(); }
	void DeleteCommandBuffer(ICommandBuffer* a_commandBuffer) override { delete a_commandBuffer; }

	inline ISynchronization* InstantiateSynchronization() override { return new VulkanSynchronization(); }
	void DeleteSynchronization(ISynchronization* a_synchronization) override { delete a_synchronization; }

	inline IRenderer* InstantiateRenderer() override { return new VulkanRenderer(); }
	void DeleteRenderer(IRenderer* a_renderDraw) override { delete a_renderDraw; }
};
