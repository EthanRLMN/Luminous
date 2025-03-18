#pragma once

#define VULKAN

#include "GLFWInputManager.hpp"
#include "IRender.hpp"
#include "VulkanDescriptor.hpp"
#include "Rendering/API/Vulkan/VulkanBuffer.hpp"
#include "Rendering/API/Vulkan/VulkanCommandPool.hpp"
#include "Rendering/API/Vulkan/VulkanDepthResource.hpp"
#include "Rendering/API/Vulkan/VulkanDevice.hpp"
#include "Rendering/API/Vulkan/VulkanFrameBuffer.hpp"
#include "Rendering/API/Vulkan/VulkanInstance.hpp"
#include "Rendering/API/Vulkan/VulkanPipeline.hpp"
#include "Rendering/API/Vulkan/VulkanRenderPass.hpp"
#include "Rendering/API/Vulkan/VulkanSurface.hpp"
#include "Rendering/API/Vulkan/VulkanSwapChain.hpp"
#include "Rendering/API/Vulkan/VulkanSynchronization.hpp"
#include "Rendering/API/Vulkan/VulkanTexture.hpp"
#include "Rendering/API/Vulkan/VulkanWindow.hpp"

class VulkanRenderInterface final : public IRender
{
public:
#ifdef VULKAN
	IInstance* InstantiateContext() override { return new VulkanInstance(); }
	void DeleteContext(IInstance* a_instance) override { delete a_instance; }

	ISurface* InstantiateSurface() override { return new VulkanSurface(); }
	void DeleteSurface(ISurface* a_surface) override { delete a_surface; }

	IDevice* InstantiateDevice() override { return new VulkanDevice(); }
	void DeleteDevice(IDevice* a_device) override { delete a_device; }

	ISwapChain* InstantiateSwapChain() override { return new VulkanSwapChain(); }
	void DeleteSwapChain(ISwapChain* a_swapChain) override { delete a_swapChain; }

	IRenderPass* InstantiateRenderPass() override { return new VulkanRenderPass(); }
	void DeleteRenderPass(IRenderPass* a_renderPass) override { delete a_renderPass; }

	IDescriptor* InstantiateDescriptor() override { return new VulkanDescriptor(); }
	void DeleteDescriptor(IDescriptor* a_descriptor) override { delete a_descriptor; }

	IPipeline* InstantiatePipeline() override { return new VulkanPipeline(); }
	void DeletePipeline(IPipeline* a_pipeline) override { delete a_pipeline; }

	ICommandPool* InstantiateCommandPool() override { return new VulkanCommandPool(); }
	void DeleteCommandPool(ICommandPool* a_commandPool) override { delete a_commandPool; }

	IDepthResource* InstantiateDepthResource() override { return new VulkanDepthResource(); }
	void DeleteDepthResource(IDepthResource* a_depthResource) override { delete a_depthResource; }

	IFrameBuffer* InstantiateFrameBuffer() override { return new VulkanFrameBuffer(); }
	void DeleteFrameBuffer(IFrameBuffer* a_frameBuffer) override { delete a_frameBuffer; }

	ITexture* InstantiateTexture() override { return new VulkanTexture(); }
	void DeleteTexture(ITexture* a_texture) override { delete a_texture; }

	IBuffer* InstantiateBuffer() override { return new VulkanBuffer(); }
	void DeleteBuffer(IBuffer* a_buffer) override { delete a_buffer; }

	ISynchronization* InstantiateSynchronization() override { return new VulkanSynchronization(); }
	void DeleteSynchronization(ISynchronization* a_synchronization) override { delete a_synchronization; }

	IWindow* InstantiateWindow() override { return new VulkanWindow(); }
	void DeleteWindow(IWindow* a_window) override { delete a_window; }

	IInputManager* InstantiateInputManager() override { return new GLFWInputManager(); }
	void DeleteInputManager(IInputManager* a_inputManager) override { delete a_inputManager; }

#endif // VULKAN
};
