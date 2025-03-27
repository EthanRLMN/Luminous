#pragma once
#include "IRenderingDraw.hpp"

#include <vulkan/vulkan.hpp>
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"
#include "Rendering/Vulkan/VulkanPipeline.hpp"
#include "Rendering/Vulkan/VulkanBuffer.hpp"
#include "Rendering/Vulkan/VulkanDescriptor.hpp"
#include "Rendering/Vulkan/VulkanRenderPass.hpp"
#include "Rendering/Vulkan/VulkanModel.hpp"
#include "Rendering/Vulkan/VulkanSynchronization.hpp"
#include "Rendering/Vulkan/VulkanCommandBuffer.hpp"


//#include "Matrix4.hpp"
//#include "Vector2.hpp"
//#include "Vector3.hpp"



class VulkanRenderingDraw final : public IRenderingDraw {

public:
	void Create(GLFWwindow* a_window, IDevice* a_device, ISwapChain* a_swapChain, IPipeline* a_pipeline, IBuffer* a_buffer, IRenderPass* a_renderPass, IDescriptor* a_descriptor, IModel* a_model, ISynchronization* a_synchronization, ICommandBuffer* a_commandBuffer) override;
	void Destroy() override;

	void RecordCommandBuffer(VkCommandBuffer a_commandBuffer, VkPipeline a_graphicsPipeline, VkPipelineLayout a_pipelineLayout, uint32_t a_imageIndex, ISwapChain* a_swapChain, IRenderPass* a_renderPass, IBuffer* a_buffer, IDescriptor* a_descriptor, IModel* a_model);



	void UpdateUniformBuffer(uint32_t currentImage, ISwapChain* a_swapChain, IBuffer* a_buffer);

	void RecreateSwapChain(GLFWwindow* a_window, IDevice* a_device);

	uint32_t m_currentFrame{ 0 };

private:
	bool m_framebufferResized{ false };
};