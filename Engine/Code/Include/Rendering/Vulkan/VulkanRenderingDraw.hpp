#pragma once
#include "IRenderingDraw.hpp"
#include "GLFW/glfw3.h"
#include <vulkan/vulkan.hpp>
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"
#include "Rendering/Vulkan/VulkanPipeline.hpp"
#include "Rendering/Vulkan/VulkanBuffer.hpp"
#include "Rendering/Vulkan/VulkanDescriptor.hpp"
#include "Rendering/Vulkan/VulkanRenderPass.hpp"
#include "Rendering/Vulkan/VulkanModel.hpp"

class VulkanRenderingDraw final : public IRenderingDraw {

public:
	void Create(GLFWwindow* a_window, IDevice* a_device, ISwapChain* a_swapChain, IPipeline* a_pipeline, IBuffer* a_buffer, IRenderPass* a_renderPass, IDescriptor* a_descriptor , IModel* a_model) override;
	void Destroy() override;

	void RecordCommandBuffer(VkCommandBuffer a_commandBuffer, VkPipeline a_graphicsPipeline, VkPipelineLayout a_pipelineLayout, uint32_t a_imageIndex, ISwapChain* a_swapChain, IRenderPass* a_renderPass, IBuffer* a_buffer, IDescriptor* a_descriptor, IModel* a_model);


private:

	std::vector<VkSemaphore> m_imageAvailableSemaphores{ VK_NULL_HANDLE };
	std::vector<VkSemaphore> m_renderFinishedSemaphores{ VK_NULL_HANDLE };
	std::vector<VkFence> m_fences{ VK_NULL_HANDLE };
};