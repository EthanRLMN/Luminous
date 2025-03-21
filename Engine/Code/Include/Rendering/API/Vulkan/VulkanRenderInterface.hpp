#pragma once

#include "IRender.hpp"

#include "Rendering/API/Vulkan/VulkanWindow.hpp"
#include "GLFWInputManager.hpp"

#include "Rendering/API/Vulkan/VulkanInstance.hpp"
#include "Rendering/API/Vulkan/VulkanSurface.hpp"
#include "Rendering/API/Vulkan/VulkanDevice.hpp"
#include "Rendering/API/Vulkan/VulkanSwapChain.hpp"
#include "Rendering/API/Vulkan/VulkanRenderPass.hpp"
#include "VulkanDescriptionSetLayout.hpp"
#include "Rendering/API/Vulkan/VulkanPipeline.hpp"
#include "Rendering/API/Vulkan/VulkanCommandPool.hpp"
#include "Rendering/API/Vulkan/VulkanDepthResource.hpp"
#include "Rendering/API/Vulkan/VulkanFrameBuffer.hpp"
#include "Rendering/API/Vulkan/VulkanInstance.hpp"
#include "Rendering/API/Vulkan/VulkanModel.hpp"
#include "Rendering/API/Vulkan/VulkanPipeline.hpp"
#include "Rendering/API/Vulkan/VulkanRenderPass.hpp"
#include "Rendering/API/Vulkan/VulkanSurface.hpp"
#include "Rendering/API/Vulkan/VulkanSwapChain.hpp"
#include "Rendering/API/Vulkan/VulkanSynchronization.hpp"
#include "Rendering/API/Vulkan/VulkanTexture.hpp"
#include "Rendering/API/Vulkan/VulkanWindow.hpp"
#include "Rendering/API/Vulkan/VulkanTexture.hpp"
#include "Rendering/API/Vulkan/VulkanModel.hpp"
#include "Rendering/API/Vulkan/VulkanBuffer.hpp"
#include "Rendering/API/Vulkan/VulkanDescriptor.hpp"
#include "Rendering/API/Vulkan/VulkanCommandBuffer.hpp"
#include "Rendering/API/Vulkan/VulkanSynchronization.hpp"

class VulkanRenderInterface final : public IRender
{
public:

	inline IWindow* InstantiateWindow() override { return new VulkanWindow(); }
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

	inline IRenderPass* InstantiateRenderPass() override { return new VulkanRenderPass(); }
	void DeleteRenderPass(IRenderPass* a_renderPass) override { delete a_renderPass; }

	inline IDescriptionSetLayout* InstantiateDescriptionSetLayout() override { return new VulkanDescriptionSetLayout(); }
	void DeleteDescriptionSetLayout(IDescriptionSetLayout* a_descriptionSetLayout) override { delete a_descriptionSetLayout; }

	inline IPipeline* InstantiatePipeline() override { return new VulkanPipeline(); }
	void DeletePipeline(IPipeline* a_pipeline) override { delete a_pipeline; }

	inline ICommandPool* InstantiateCommandPool() override { return new VulkanCommandPool(); }
	void DeleteCommandPool(ICommandPool* a_commandPool) override { delete a_commandPool; }

	inline IDepthResource* InstantiateDepthResource() override { return new VulkanDepthResource(); }
	void DeleteDepthResource(IDepthResource* a_depthResource) override { delete a_depthResource; }

	inline IFrameBuffer* InstantiateFrameBuffer() override { return new VulkanFrameBuffer(); }
	void DeleteFrameBuffer(IFrameBuffer* a_frameBuffer) override { delete a_frameBuffer; }

	inline ITexture* InstantiateTexture() override { return new VulkanTexture(); }
	void DeleteTexture(ITexture* a_texture) override { delete a_texture; }

	inline IModel* InstantiateModel() override { return new VulkanModel(); }
	void DeleteModel(IModel* a_model) override { delete a_model; }

	inline IBuffer* InstantiateBuffer() override { return new VulkanBuffer(); }
	void DeleteBuffer(IBuffer* a_buffer) override { delete a_buffer; }

	inline IDescriptor* InstantiateDescriptor() override { return new VulkanDescriptor(); }
	void DeleteDescriptor(IDescriptor* a_descriptor) override { delete a_descriptor; }

	inline ICommandBuffer* InstantiateCommandBuffer() override { return new VulkanCommandBuffer(); }
	void DeleteCommandBuffer(ICommandBuffer* a_commandBuffer) override { delete a_commandBuffer; }


	inline ISynchronization* InstantiateSynchronization() override { return new VulkanSynchronization(); }
	void DeleteSynchronization(ISynchronization* a_synchronization) override { delete a_synchronization; }

};
