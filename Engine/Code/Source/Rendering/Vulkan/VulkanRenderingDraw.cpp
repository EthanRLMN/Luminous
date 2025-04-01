#include "ICommandBuffer.hpp"
#include "IDepthResource.hpp"
#include "IDescriptor.hpp"
#include "IFrameBuffer.hpp"
#include "IModel.hpp"
#include "IPipeline.hpp"
#include "IRenderPass.hpp"
#include "ISwapChain.hpp"
#include "ISynchronization.hpp"

#include "Rendering/Vulkan/VulkanRenderingDraw.hpp"

#include "Matrix4.hpp"
#include "Rendering/Vulkan/VulkanBuffer.hpp"
#include "Rendering/Vulkan/VulkanCommandBuffer.hpp"
#include "Rendering/Vulkan/VulkanDepthResource.hpp"
#include "Rendering/Vulkan/VulkanDescriptor.hpp"
#include "Rendering/Vulkan/VulkanFrameBuffer.hpp"
#include "Rendering/Vulkan/VulkanModel.hpp"
#include "Rendering/Vulkan/VulkanPipeline.hpp"
#include "Rendering/Vulkan/VulkanRenderPass.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"
#include "Rendering/Vulkan/VulkanSynchronization.hpp"

#include "MathUtils.hpp"


void VulkanRenderingDraw::Create(IWindow* a_window, IDevice* a_device, ISwapChain* a_swapChain, IPipeline* a_pipeline, IBuffer* a_buffer, IRenderPass* a_renderPass, IDescriptor* a_descriptor, IModel* a_model, ISynchronization* a_synchronization, ICommandBuffer* a_commandBuffer, IFrameBuffer* a_frameBuffer, IDepthResource* a_depthResource, ISurface* a_surface)
{
	vkWaitForFences(a_device->CastVulkan()->GetDevice(), 1, &a_synchronization->CastVulkan()->GetFences()[m_currentFrame], VK_TRUE, UINT64_MAX);

	uint32_t l_imageIndex { 0 };
	VkResult l_result = vkAcquireNextImageKHR(a_device->CastVulkan()->GetDevice(), a_swapChain->CastVulkan()->GetSwapChain(), UINT64_MAX, a_synchronization->CastVulkan()->GetImageAvailableSemaphores()[m_currentFrame], nullptr, &l_imageIndex);

	if (l_result == VK_ERROR_OUT_OF_DATE_KHR)
	{
		RecreateSwapChain(a_window, a_device, a_surface, a_swapChain, a_depthResource, a_frameBuffer, a_renderPass);
		return;
	}
	if (l_result != VK_SUCCESS && l_result != VK_SUBOPTIMAL_KHR)
		DEBUG_LOG_ERROR("failed to acquire swap chain image");

	UpdateUniformBuffer(m_currentFrame, a_swapChain, a_buffer);
	vkResetFences(a_device->CastVulkan()->GetDevice(), 1, &a_synchronization->CastVulkan()->GetFences()[m_currentFrame]);

	VkSubmitInfo l_submitInfo { VK_STRUCTURE_TYPE_SUBMIT_INFO };

	const VkSemaphore l_waitSemaphores[] = { a_synchronization->CastVulkan()->GetImageAvailableSemaphores()[m_currentFrame] };
	const VkPipelineStageFlags l_waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	l_submitInfo.waitSemaphoreCount = 1;
	l_submitInfo.pWaitSemaphores = l_waitSemaphores;
	l_submitInfo.pWaitDstStageMask = l_waitStages;
	l_submitInfo.commandBufferCount = 1;
	l_submitInfo.pCommandBuffers = &a_commandBuffer->CastVulkan()->GetCommandBuffers()[m_currentFrame];

	const VkSemaphore l_signalSemaphores[] = { a_synchronization->CastVulkan()->GetRenderFinishedSemaphores()[m_currentFrame] };
	l_submitInfo.signalSemaphoreCount = 1;
	l_submitInfo.pSignalSemaphores = l_signalSemaphores;

	vkResetCommandBuffer(a_commandBuffer->CastVulkan()->GetCommandBuffers()[m_currentFrame], 0);
	RecordCommandBuffer(a_commandBuffer->CastVulkan()->GetCommandBuffers()[m_currentFrame], a_pipeline->CastVulkan()->GetGraphicsPipeline(), a_pipeline->CastVulkan()->GetPipelineLayout(), l_imageIndex, a_swapChain, a_renderPass, a_buffer, a_descriptor, a_model, a_frameBuffer);

	if (vkQueueSubmit(a_device->CastVulkan()->GetGraphicsQueue(), 1, &l_submitInfo, a_synchronization->CastVulkan()->GetFences()[m_currentFrame]) != VK_SUCCESS)
		DEBUG_LOG_ERROR("Failed to submit draw command buffer");

	VkPresentInfoKHR l_presentInfo { VK_STRUCTURE_TYPE_PRESENT_INFO_KHR };
	l_presentInfo.waitSemaphoreCount = 1;
	l_presentInfo.pWaitSemaphores = l_signalSemaphores;

	const VkSwapchainKHR l_swapChains[] = { a_swapChain->CastVulkan()->GetSwapChain() };
	l_presentInfo.swapchainCount = 1;
	l_presentInfo.pSwapchains = l_swapChains;
	l_presentInfo.pImageIndices = &l_imageIndex;

	l_result = vkQueuePresentKHR(a_device->CastVulkan()->GetPresentationQueue(), &l_presentInfo);

	if (l_result == VK_ERROR_OUT_OF_DATE_KHR || l_result == VK_SUBOPTIMAL_KHR) { RecreateSwapChain(a_window, a_device, a_surface, a_swapChain, a_depthResource, a_frameBuffer, a_renderPass); } else if (l_result != VK_SUCCESS)
		DEBUG_LOG_ERROR("failed to present swap chain image");

	m_currentFrame = (m_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}


void VulkanRenderingDraw::RecordCommandBuffer(const VkCommandBuffer a_commandBuffer, const VkPipeline a_graphicsPipeline, const VkPipelineLayout a_pipelineLayout, const uint32_t a_imageIndex, ISwapChain* a_swapChain, IRenderPass* a_renderPass, IBuffer* a_buffer, IDescriptor* a_descriptor, IModel* a_model, IFrameBuffer* a_frameBuffer) const
{
	const VkCommandBufferBeginInfo l_bufferBeginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };

	if (vkBeginCommandBuffer(a_commandBuffer, &l_bufferBeginInfo) != VK_SUCCESS)
		DEBUG_LOG_INFO("failed to begin recording command buffer!\n");

	VkRenderPassBeginInfo l_renderPassBeginInfo = { VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO };
	l_renderPassBeginInfo.renderPass = a_renderPass->CastVulkan()->GetRenderPass();
	l_renderPassBeginInfo.framebuffer = a_frameBuffer->CastVulkan()->GetFrameBuffers()[a_imageIndex];
	l_renderPassBeginInfo.renderArea.offset = { 0, 0 };
	l_renderPassBeginInfo.renderArea.extent = a_swapChain->CastVulkan()->GetSwapChainExtent();

	std::array<VkClearValue, 2> clearValues { };
	clearValues[0].color = { { 0.0f, 0.0f, 0.0f, 1.0f } };
	clearValues[1].depthStencil = { 1.0f, 0 };

	l_renderPassBeginInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
	l_renderPassBeginInfo.pClearValues = clearValues.data();

	vkCmdBeginRenderPass(a_commandBuffer, &l_renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
	vkCmdBindPipeline(a_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, a_graphicsPipeline);

	VkViewport l_viewport { };
	l_viewport.x = 0.0f;
	l_viewport.y = 0.0f;
	l_viewport.width = static_cast<float>(a_swapChain->CastVulkan()->GetSwapChainExtent().width);
	l_viewport.height = static_cast<float>(a_swapChain->CastVulkan()->GetSwapChainExtent().height);
	l_viewport.minDepth = 0.0f;
	l_viewport.maxDepth = 1.0f;
	vkCmdSetViewport(a_commandBuffer, 0, 1, &l_viewport);

	VkRect2D l_scissor { };
	l_scissor.offset = { 0, 0 };
	l_scissor.extent = a_swapChain->CastVulkan()->GetSwapChainExtent();
	vkCmdSetScissor(a_commandBuffer, 0, 1, &l_scissor);

	const VkBuffer l_vertexBuffers[] = { a_buffer->CastVulkan()->GetVertexBuffer() };
	const VkDeviceSize l_offsets[] = { 0 };
	vkCmdBindVertexBuffers(a_commandBuffer, 0, 1, l_vertexBuffers, l_offsets);
	vkCmdBindIndexBuffer(a_commandBuffer, a_buffer->CastVulkan()->CastVulkan()->GetIndexBuffer(), 0, VK_INDEX_TYPE_UINT32);

	vkCmdBindDescriptorSets(a_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, a_pipelineLayout, 0, 1, &a_descriptor->CastVulkan()->GetDescriptorSet()[m_currentFrame], 0, nullptr);
	vkCmdDrawIndexed(a_commandBuffer, static_cast<uint32_t>(a_model->CastVulkan()->GetIndices().size()), 1, 0, 0, 0);
	vkCmdEndRenderPass(a_commandBuffer);

	const VkResult l_result = vkEndCommandBuffer(a_commandBuffer);
	if (l_result != VK_SUCCESS)
		throw std::runtime_error("Failed to stop recording a command buffer ");
}


void VulkanRenderingDraw::UpdateUniformBuffer(const uint32_t currentImage, ISwapChain* a_swapChain, IBuffer* a_buffer)
{
	static std::chrono::steady_clock::time_point l_startTime = std::chrono::high_resolution_clock::now();
	const std::chrono::steady_clock::time_point l_currentTime = std::chrono::high_resolution_clock::now();
	const float l_time = std::chrono::duration<float, std::chrono::seconds::period>(l_currentTime - l_startTime).count();

	UniformBufferObject l_ubo { };
	l_ubo.model = Maths::Matrix4::Rotate(Maths::Matrix4(1.0f), l_time * Maths::DegToRad(90.0f), Maths::Vector3(0.0f, 0.0f, 1.0f));
	l_ubo.view = Maths::Matrix4::LookAt(Maths::Vector3(2.0f, 2.0f, 2.0f), Maths::Vector3(0.0f, 0.0f, 0.0f), Maths::Vector3(0.0f, 0.0f, 1.0f));
	l_ubo.proj = Maths::Matrix4::Perspective(Maths::DegToRad(45.f), a_swapChain->CastVulkan()->GetSwapChainExtent().width / static_cast<float>(a_swapChain->CastVulkan()->GetSwapChainExtent().height), 0.1f, 10.0f);
	l_ubo.proj = l_ubo.proj.Opposite();

	memcpy(a_buffer->CastVulkan()->GetUniformBuffersMapped()[currentImage], &l_ubo, sizeof(l_ubo));
}


void VulkanRenderingDraw::RecreateSwapChain(IWindow* a_window, IDevice* a_device, ISurface* a_surface, ISwapChain* a_swapChain, IDepthResource* a_depthResource, IFrameBuffer* a_frameBuffer, IRenderPass* a_renderPass)
{
	int l_width = 0, l_height = 0;

	glfwGetFramebufferSize(a_window->CastGLFW()->GetGLFWWindow(), &l_width, &l_height);
	while (l_width == 0 || l_height == 0)
	{
		glfwGetFramebufferSize(a_window->CastGLFW()->GetGLFWWindow(), &l_width, &l_height);
		glfwWaitEvents();
	}

	CleanupSwapChain(a_device, a_swapChain, a_depthResource, a_frameBuffer);

	vkDeviceWaitIdle(a_device->CastVulkan()->GetDevice());

	a_swapChain->CastVulkan()->Create(a_window, a_device, a_surface);
	CreateImageViews(a_device, a_swapChain);
	a_depthResource->CastVulkan()->Create(a_device, a_swapChain, a_renderPass);
	a_frameBuffer->CastVulkan()->Create(a_device, a_swapChain, a_renderPass, a_depthResource);
}


void VulkanRenderingDraw::CleanupSwapChain(IDevice* a_device, ISwapChain* a_swapChain, IDepthResource* a_depthResource, IFrameBuffer* a_framebuffer)
{
	vkDeviceWaitIdle(a_device->CastVulkan()->GetDevice());

	for (const auto framebuffer : a_framebuffer->CastVulkan()->GetFrameBuffers())
		vkDestroyFramebuffer(a_device->CastVulkan()->GetDevice(), framebuffer, nullptr);

	for (const auto imageView : a_swapChain->CastVulkan()->GetSwapChainImageViews())
		vkDestroyImageView(a_device->CastVulkan()->GetDevice(), imageView, nullptr);

	vkDestroyImageView(a_device->CastVulkan()->GetDevice(), a_depthResource->CastVulkan()->GetDepthImageView(), nullptr);
	vkDestroyImage(a_device->CastVulkan()->GetDevice(), a_depthResource->CastVulkan()->GetDepthImage(), nullptr);
	vkFreeMemory(a_device->CastVulkan()->GetDevice(), a_depthResource->CastVulkan()->GetDepthImageMemory(), nullptr);

	vkDestroySwapchainKHR(a_device->CastVulkan()->GetDevice(), a_swapChain->CastVulkan()->GetSwapChain(), nullptr);
}


void VulkanRenderingDraw::CreateImageViews(IDevice* a_device, ISwapChain* a_swapChain)
{
	a_swapChain->CastVulkan()->GetSwapChainImageViews().resize(a_swapChain->CastVulkan()->GetSwapChainImages().size());

	for (uint32_t i = 0; i < a_swapChain->CastVulkan()->GetSwapChainImages().size(); ++i)
		a_swapChain->CastVulkan()->GetSwapChainImageViews()[i] = a_swapChain->CastVulkan()->CreateImageView(a_swapChain->CastVulkan()->GetSwapChainImages()[i], a_device->CastVulkan()->GetDevice(), a_swapChain->CastVulkan()->GetSwapChainImageFormat(), VK_IMAGE_ASPECT_COLOR_BIT);
}
