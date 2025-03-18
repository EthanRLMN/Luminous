#pragma once

#define VULKAN

#include "IRender.hpp"
#include "GLFWInputManager.hpp"
#include "Rendering/API/Vulkan/VulkanWindow.hpp"
#include "Rendering/API/Vulkan/VulkanInstance.hpp"
#include "Rendering/API/Vulkan/VulkanSurface.hpp"
#include "Rendering/API/Vulkan/VulkanDevice.hpp"
#include "Rendering/API/Vulkan/VulkanSwapChain.hpp"
#include "Rendering/API/Vulkan/VulkanRenderPass.hpp"
#include "Rendering/API/Vulkan/VulkanDescriptions.hpp"
#include "Rendering/API/Vulkan/VulkanBuffer.hpp"
#include "Rendering/API/Vulkan/VulkanPipeline.hpp"
#include "Rendering/API/Vulkan/VulkanCommandPool.hpp"
#include "Rendering/API/Vulkan/VulkanDepthRessource.hpp"
#include "Rendering/API/Vulkan/VulkanFrameBuffer.hpp"
#include "Rendering/API/Vulkan/VulkanTexture.hpp"


#include "Rendering/API/Vulkan/VulkanSynchronisation.hpp"

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

	IDescriptions* InstantiateDescriptions() override { return new VulkanDescriptions(); }
	void DeleteDescriptions(IDescriptions* a_descriptions) override { delete a_descriptions; }

	IPipeline* InstantiatePipeline() override { return new VulkanPipeline(); }
	void DeletePipeline(IPipeline* a_pipeline) override { delete a_pipeline; }

	ICommandPool* InstantiateCommandPool() override { return new VulkanCommandPool(); }
	void DeleteCommandPool(ICommandPool* a_commandPool) override { delete a_commandPool; }

	IDepthRessource* InstantiateDepthRessource() override { return new VulkanDepthRessource(); }
	void DeleteDepthRessource(IDepthRessource* a_depthRessource) override { delete a_depthRessource; }

	IFrameBuffer* InstantiateFrameBuffer() override { return new VulkanFrameBuffer(); }
	void DeleteFrameBuffer(IFrameBuffer* a_frameBuffer) override { delete a_frameBuffer; }

	ITexture* InstantiateTexture() override { return new VulkanTexture(); }
	void DeleteTexture(ITexture* a_texture) override { delete a_texture; }

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
