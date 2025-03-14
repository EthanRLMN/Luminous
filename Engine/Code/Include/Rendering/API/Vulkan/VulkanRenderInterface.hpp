#pragma once

#define VULKAN

#include "GLFWInputManager.hpp"
#include "Rendering/API/Vulkan/VulkanBuffer.hpp"
#include "Rendering/API/Vulkan/VulkanDevice.hpp"
#include "Rendering/API/Vulkan/VulkanInstance.hpp"
#include "Rendering/API/Vulkan/VulkanPipeline.hpp"
#include "Rendering/API/Vulkan/VulkanRenderPass.hpp"
#include "Rendering/API/Vulkan/VulkanSurface.hpp"
#include "Rendering/API/Vulkan/VulkanSwapChain.hpp"
#include "Rendering/API/Vulkan/VulkanSynchronisation.hpp"
#include "Rendering/API/Vulkan/VulkanWindow.hpp"

class VulkanRenderInterface : public IRender
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
	void DeleteSwapChain(ISwapChain* a_swapchain) override { delete a_swapchain; }

	IRenderPass* InstantiateRenderPass() override { return new VulkanRenderPass(); }
	void DeleteRenderPass(IRenderPass* a_renderpass) override { delete a_renderpass; }

	IPipeline* InstantiatePipeline() override { return new VulkanPipeline(); }
	void DeletePipeline(IPipeline* a_pipeline) override { delete a_pipeline; }

	IBuffer* InstantiateBuffer() override { return new VulkanBuffer(); }
	void DeleteBuffer(IBuffer* a_buffer) override { delete a_buffer; }

	ISynchronisation* InstantiateSynchronisation() override { return new VulkanSynchronisation(); }
	void DeleteSynchronisation(ISynchronisation* a_synchronisation) override { delete a_synchronisation; }

	IWindow* InstantiateWindow() override { return new VulkanWindow(); }
	void DeleteWindow(IWindow* a_window) override { delete a_window; }

	IInputManager* InstantiateInputManager() override { return new GLFWInputManager(); }
	void DeleteInputManager(IInputManager* a_inputManager) override { delete a_inputManager; }

#endif // VULKAN
};
