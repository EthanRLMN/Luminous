#pragma once


#define VULKAN
#include "IDevice.hpp"
#include "IInstance.hpp"
#include "IPipeline.hpp"
#include "IRender.hpp"
#include "ISurface.hpp"
#include "ISwapChain.hpp"
#include "ISynchronisation.hpp"
#include "API/Vulkan/VulkanBuffer.hpp"
#include "API/Vulkan/VulkanDevice.hpp"
#include "API/Vulkan/VulkanInstance.hpp"
#include "API/Vulkan/VulkanPipeline.hpp"
#include "API/Vulkan/VulkanRenderPass.hpp"
#include "API/Vulkan/VulkanSurface.hpp"
#include "API/Vulkan/VulkanSwapChain.hpp"
#include "API/Vulkan/VulkanSynchronisation.hpp"

class IRenderHardwareInterface : public IRender
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

#endif // VULKAN
};
