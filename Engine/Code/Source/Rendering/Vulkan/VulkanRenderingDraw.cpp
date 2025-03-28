#include "Rendering/Vulkan/VulkanRenderingDraw.hpp"


void VulkanRenderingDraw::Create(GLFWwindow* a_window, IDevice* a_device, ISwapChain* a_swapChain,
                                 IPipeline* a_pipeline, IBuffer* a_buffer, IRenderPass* a_renderPass,
                                 IDescriptor* a_descriptor, IModel* a_model, ISynchronization* a_synchronization,
                                 ICommandBuffer* a_commandBuffer, IFrameBuffer* a_frameBuffer)
{
	vkWaitForFences(a_device->CastVulkan()->GetDevice(), 1,
	                &a_synchronization->CastVulkan()->GetFences()[m_currentFrame], VK_TRUE, UINT64_MAX);

	uint32_t l_imageIndex;
	VkResult l_result = vkAcquireNextImageKHR(a_device->CastVulkan()->GetDevice(),
	                                          a_swapChain->CastVulkan()->GetSwapChain(), UINT64_MAX,
	                                          a_synchronization->CastVulkan()->GetImageAvailableSemaphores()[
		                                          m_currentFrame], VK_NULL_HANDLE, &l_imageIndex);

	if (l_result == VK_ERROR_OUT_OF_DATE_KHR)
	{
		//RecreateSwapChain(a_window,mainDevice.logicalDevice);
		return;
	}
	if (l_result != VK_SUCCESS && l_result != VK_SUBOPTIMAL_KHR)
	{
		DEBUG_LOG_ERROR("failed to acquire swap chain image");
	}

	UpdateUniformBuffer(m_currentFrame, a_swapChain, a_buffer);

	vkResetFences(a_device->CastVulkan()->GetDevice(), 1,
	              &a_synchronization->CastVulkan()->GetFences()[m_currentFrame]);


	VkSubmitInfo l_submitInfo{};
	l_submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	const VkSemaphore l_waitSemaphores[] = {
		a_synchronization->CastVulkan()->GetImageAvailableSemaphores()[m_currentFrame]
	};
	constexpr VkPipelineStageFlags l_waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	l_submitInfo.waitSemaphoreCount = 1;
	l_submitInfo.pWaitSemaphores = l_waitSemaphores;
	l_submitInfo.pWaitDstStageMask = l_waitStages;

	l_submitInfo.commandBufferCount = 1;
	l_submitInfo.pCommandBuffers = &a_commandBuffer->CastVulkan()->GetCommandBuffers()[m_currentFrame];

	const VkSemaphore l_signalSemaphores[] = {a_synchronization->CastVulkan()->GetRenderFinishedSemaphores()[m_currentFrame]};

	l_submitInfo.signalSemaphoreCount = 1;
	l_submitInfo.pSignalSemaphores = l_signalSemaphores;

	vkResetCommandBuffer(a_commandBuffer->CastVulkan()->GetCommandBuffers()[m_currentFrame], 0);
	RecordCommandBuffer(a_commandBuffer->CastVulkan()->GetCommandBuffers()[m_currentFrame],
	                    a_pipeline->CastVulkan()->GetGraphicsPipeline(), a_pipeline->CastVulkan()->GetPipelineLayout(),
	                    l_imageIndex, a_swapChain, a_renderPass, a_buffer, a_descriptor, a_model, a_frameBuffer);

	if (vkQueueSubmit(a_device->CastVulkan()->GetGraphicsQueue(), 1, &l_submitInfo, a_synchronization->CastVulkan()->GetFences()[m_currentFrame]) != VK_SUCCESS)
		DEBUG_LOG_ERROR("Failed to submit draw command buffer");

	VkPresentInfoKHR l_presentInfo{};
	l_presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	l_presentInfo.waitSemaphoreCount = 1;
	l_presentInfo.pWaitSemaphores = l_signalSemaphores;

	const VkSwapchainKHR l_swapChains[] = {a_swapChain->CastVulkan()->GetSwapChain()};
	l_presentInfo.swapchainCount = 1;
	l_presentInfo.pSwapchains = l_swapChains;
	l_presentInfo.pImageIndices = &l_imageIndex;

	l_result = vkQueuePresentKHR(a_device->CastVulkan()->GetPresentationQueue(), &l_presentInfo);

	if (l_result == VK_ERROR_OUT_OF_DATE_KHR || l_result == VK_SUBOPTIMAL_KHR || m_framebufferResized)
	{
		m_framebufferResized = false;
		//RecreateSwapChain(a_window,mainDevice.logicalDevice);
	} else if (l_result != VK_SUCCESS)
	{
		DEBUG_LOG_ERROR("failed to present swap chain image");
	}

	m_currentFrame = (m_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void VulkanRenderingDraw::Destroy()
{
}


void VulkanRenderingDraw::RecordCommandBuffer(const VkCommandBuffer a_commandBuffer, const VkPipeline a_graphicsPipeline,
                                              const VkPipelineLayout a_pipelineLayout, const uint32_t a_imageIndex,
                                              ISwapChain* a_swapChain, IRenderPass* a_renderPass, IBuffer* a_buffer,
                                              IDescriptor* a_descriptor, IModel* a_model, IFrameBuffer* a_frameBuffer) const
{
	VkCommandBufferBeginInfo l_bufferBeginInfo = {};
	l_bufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

	if (vkBeginCommandBuffer(a_commandBuffer, &l_bufferBeginInfo) != VK_SUCCESS)
		DEBUG_LOG_INFO("failed to begin recording command buffer!\n");


	VkRenderPassBeginInfo l_renderPassBeginInfo = {};
	l_renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	l_renderPassBeginInfo.renderPass = a_renderPass->CastVulkan()->GetRenderPass();
	l_renderPassBeginInfo.framebuffer = a_frameBuffer->CastVulkan()->GetFrameBuffers()[a_imageIndex];
	l_renderPassBeginInfo.renderArea.offset = {0, 0};
	l_renderPassBeginInfo.renderArea.extent = a_swapChain->CastVulkan()->GetSwapChainExtent();

	std::array<VkClearValue, 2> clearValues{};
	clearValues[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
	clearValues[1].depthStencil = {1.0f, 0};

	l_renderPassBeginInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
	l_renderPassBeginInfo.pClearValues = clearValues.data();

	vkCmdBeginRenderPass(a_commandBuffer, &l_renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
	vkCmdBindPipeline(a_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, a_graphicsPipeline);

	VkViewport l_viewport{};
	l_viewport.x = 0.0f;
	l_viewport.y = 0.0f;
	l_viewport.width = static_cast<float>(a_swapChain->CastVulkan()->GetSwapChainExtent().width);
	l_viewport.height = static_cast<float>(a_swapChain->CastVulkan()->GetSwapChainExtent().height);
	l_viewport.minDepth = 0.0f;
	l_viewport.maxDepth = 1.0f;
	vkCmdSetViewport(a_commandBuffer, 0, 1, &l_viewport);

	VkRect2D l_scissor{};
	l_scissor.offset = {0, 0};
	l_scissor.extent = a_swapChain->CastVulkan()->GetSwapChainExtent();
	vkCmdSetScissor(a_commandBuffer, 0, 1, &l_scissor);

	const VkBuffer l_vertexBuffers[] = {a_buffer->CastVulkan()->GetVertexBuffer()};
	const VkDeviceSize l_offsets[] = { 0 };
	vkCmdBindVertexBuffers(a_commandBuffer, 0, 1, l_vertexBuffers, l_offsets);
	vkCmdBindIndexBuffer(a_commandBuffer, a_buffer->CastVulkan()->GetIndexBuffer(), 0, VK_INDEX_TYPE_UINT32);

	vkCmdBindDescriptorSets(a_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, a_pipelineLayout, 0, 1,
	                        &a_descriptor->CastVulkan()->GetDescriptorSet()[m_currentFrame], 0, nullptr);

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

	UniformBufferObject l_ubo{};
	l_ubo.model = glm::rotate(glm::mat4(1.0f), l_time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	l_ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	l_ubo.proj = glm::perspective(glm::radians(45.0f), a_swapChain->CastVulkan()->GetSwapChainExtent().width / static_cast<float>(a_swapChain->CastVulkan()->GetSwapChainExtent().height), 0.1f, 10.0f);
	l_ubo.proj[1][1] *= -1;

	memcpy(a_buffer->CastVulkan()->GetUniformBuffersMapped()[currentImage], &l_ubo, sizeof(l_ubo));
}

/*
void VulkanRenderingDraw::RecreateSwapChain(GLFWwindow* a_window, VkDevice a_device)
{
	int l_width = 0, l_height = 0;

	glfwGetFramebufferSize(a_window, &l_width, &l_height);
	while (l_width == 0 || l_height == 0) {
		glfwGetFramebufferSize(a_window, &l_width, &l_height);
		glfwWaitEvents();
	}

	CleanUpSwapChain();

	vkDeviceWaitIdle(a_device);

	CreateSwapChain(a_window);
	CreateImageViews(a_device);
	CreateDepthRessource();
	CreateFrameBuffers();
}
*/
