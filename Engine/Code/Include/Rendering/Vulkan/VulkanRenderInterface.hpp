#pragma once

#include "IRender.hpp"

#include "Core/GLFW/GLFWInputManager.hpp"
#include "Core/GLFW/GLFWWindow.hpp"

#include "VulkanDescriptorSetLayout.hpp"
#include "Rendering/Vulkan/VulkanBuffer.hpp"
#include "Rendering/Vulkan/VulkanCommandBuffer.hpp"
#include "Rendering/Vulkan/VulkanCommandPool.hpp"
#include "Rendering/Vulkan/VulkanDepthResource.hpp"
#include "Rendering/Vulkan/VulkanDescriptor.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanFrameBuffer.hpp"
#include "Rendering/Vulkan/VulkanInstance.hpp"
#include "Rendering/Vulkan/VulkanMesh.hpp"
#include "Rendering/Vulkan/VulkanPipeline.hpp"
#include "Rendering/Vulkan/VulkanRenderPass.hpp"
#include "Rendering/Vulkan/VulkanSurface.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"
#include "Rendering/Vulkan/VulkanSynchronization.hpp"
#include "Rendering/Vulkan/VulkanTexture.hpp"
#include "Rendering/Vulkan/VulkanMultiSampling.hpp"

#include "Rendering/Vulkan/VulkanRenderer.hpp"

class VulkanRenderInterface final : public IRender
{
public:

	__forceinline IWindow* InstantiateWindow() override { return new GLFWWindow(); }
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

	inline IDescriptorSetLayout* InstantiateDescriptorSetLayout() override { return new VulkanDescriptorSetLayout(); }
	void DeleteDescriptorSetLayout(IDescriptorSetLayout* a_descriptorSetLayout) override { delete a_descriptorSetLayout; }

	inline IPipeline* InstantiatePipeline() override { return new VulkanPipeline(); }
	void DeletePipeline(IPipeline* a_pipeline) override { delete a_pipeline; }

	inline ICommandPool* InstantiateCommandPool() override { return new VulkanCommandPool(); }
	void DeleteCommandPool(ICommandPool* a_commandPool) override { delete a_commandPool; }

	inline IMultiSampling* InstantiateMultiSampling() override { return new VulkanMultiSampling(); }

	inline IDepthResource* InstantiateDepthResource() override { return new VulkanDepthResource(); }
	void DeleteDepthResource(IDepthResource* a_depthResource) override { delete a_depthResource; }

	inline IFrameBuffer* InstantiateFrameBuffer() override { return new VulkanFrameBuffer(); }
	void DeleteFrameBuffer(IFrameBuffer* a_frameBuffer) override { delete a_frameBuffer; }

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

	inline IResourceManager* InstantiateResourceManager() override { return new IResourceManager(); }
	void DeleteResourceManager(IResourceManager* a_resourceManager) override { delete a_resourceManager; }

	inline IRenderer* InstantiateRenderingDraw() override { return new VulkanRenderer(); }
	void DeleteRenderingDraw(IRenderer* a_renderDraw) override { delete a_renderDraw; }

};
