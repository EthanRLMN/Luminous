#include "Rendering/Vulkan/VulkanRenderingDraw.hpp"

void VulkanRenderingDraw::Create(GLFWwindow* a_window, IDevice* a_device, ISwapChain* a_swapChain, IPipeline* a_pipeline, IBuffer* a_buffer, IRenderPass* a_renderPass, IDescriptor* a_descriptor ,IModel* a_model)
{
	vkWaitForFences(a_device->CastVulkan()->GetDevice(), 1, &m_fences[currentFrame], VK_TRUE, UINT64_MAX);

	uint32_t l_imageIndex;
	VkResult l_result = vkAcquireNextImageKHR(a_device->CastVulkan()->GetDevice(), a_swapChain->CastVulkan()->GetSwapChain(), UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &l_imageIndex);

	if (l_result == VK_ERROR_OUT_OF_DATE_KHR) {
		RecreateSwapChain(a_window, a_device->CastVulkan()->GetDevice());
		return;
	}
	else if (l_result != VK_SUCCESS && l_result != VK_SUBOPTIMAL_KHR)
	{
		DEBUG_LOG_ERROR("failed to acquire swap chain image\n");
	}

	UpdateUniformBuffer(currentFrame);

	vkResetFences(a_device->CastVulkan()->GetDevice(), 1, &m_fences[currentFrame]);

	vkResetCommandBuffer(a_swapChain->CastVulkan()->GetCommandBuffers()[currentFrame], 0);
	RecordCommandBuffer(a_swapChain->CastVulkan()->GetCommandBuffers()[currentFrame], a_pipeline->CastVulkan()->GetGraphicsPipeline(), a_pipeline->CastVulkan()->GetPipelineLayout(), l_imageIndex, a_swapChain, a_renderPass, a_buffer, a_descriptor);


	VkSubmitInfo l_submitInfo{};
	l_submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	l_submitInfo.waitSemaphoreCount = 1;
	l_submitInfo.pWaitSemaphores = waitSemaphores;
	l_submitInfo.pWaitDstStageMask = waitStages;

	l_submitInfo.commandBufferCount = 1;
	l_submitInfo.pCommandBuffers = &a_swapChain->CastVulkan()->GetCommandBuffers()[currentFrame];

	VkSemaphore l_signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };

	l_submitInfo.signalSemaphoreCount = 1;
	l_submitInfo.pSignalSemaphores = l_signalSemaphores;

	if (vkQueueSubmit(a_device->CastVulkan()->GetGraphicsQueue(), 1, &l_submitInfo, m_fences[currentFrame]) != VK_SUCCESS) {
		DEBUG_LOG_ERROR("Failed to submit draw command buffer\n");
	}

	VkPresentInfoKHR l_presentInfo{};
	l_presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	l_presentInfo.waitSemaphoreCount = 1;
	l_presentInfo.pWaitSemaphores = l_signalSemaphores;

	VkSwapchainKHR l_swapChains[] = { a_swapChain->CastVulkan()->GetSwapChain() };
	l_presentInfo.swapchainCount = 1;
	l_presentInfo.pSwapchains = l_swapChains;
	l_presentInfo.pImageIndices = &l_imageIndex;

	l_result = vkQueuePresentKHR(a_device->CastVulkan()->GetPresentationQueue(), &l_presentInfo);

	if (l_result == VK_ERROR_OUT_OF_DATE_KHR || l_result == VK_SUBOPTIMAL_KHR || framebufferResized) {
		framebufferResized = false;
		RecreateSwapChain(a_window, a_device->CastVulkan()->GetDevice());
	}
	else if (l_result != VK_SUCCESS) {
		DEBUG_LOG_ERROR("failed to present swap chain image\n");
	}

	currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void VulkanRenderingDraw::Destroy()
{
}


void VulkanRenderingDraw::RecordCommandBuffer(VkCommandBuffer a_commandBuffer, VkPipeline a_graphicsPipeline, VkPipelineLayout a_pipelineLayout, uint32_t a_imageIndex, ISwapChain* a_swapChain, IRenderPass* a_renderPass, IBuffer* a_buffer, IDescriptor* a_descriptor, IModel* a_model)
{
	VkCommandBufferBeginInfo l_bufferBeginInfo = {};
	l_bufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

	if (vkBeginCommandBuffer(a_commandBuffer, &l_bufferBeginInfo) != VK_SUCCESS) {
		DEBUG_LOG_INFO("failed to begin recording command buffer!\n");
	}


	VkRenderPassBeginInfo l_renderPassBeginInfo = {};

	l_renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	l_renderPassBeginInfo.renderPass = a_renderPass->CastVulkan()->GetRenderPass();
	l_renderPassBeginInfo.framebuffer = a_swapChain->CastVulkan()->GetSwapChainFrameBuffers()[a_imageIndex];
	l_renderPassBeginInfo.renderArea.offset = { 0,0 };
	l_renderPassBeginInfo.renderArea.extent = a_swapChain->CastVulkan()->GetSwapChainExtent();

	std::array <VkClearValue, 2> clearValues{};
	clearValues[0].color = { {0.0f, 0.0f, 0.0f, 1.0f} };
	clearValues[1].depthStencil = { 1.0f,0 };

	l_renderPassBeginInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
	l_renderPassBeginInfo.pClearValues = clearValues.data();

	vkCmdBeginRenderPass(a_commandBuffer, &l_renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
	vkCmdBindPipeline(a_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, a_graphicsPipeline);

	VkViewport l_viewport{};
	l_viewport.x = 0.0f;
	l_viewport.y = 0.0f;
	l_viewport.width = (float)a_swapChain->CastVulkan()->GetSwapChainExtent().width;
	l_viewport.height = (float)a_swapChain->CastVulkan()->GetSwapChainExtent().height;
	l_viewport.minDepth = 0.0f;
	l_viewport.maxDepth = 1.0f;
	vkCmdSetViewport(a_commandBuffer, 0, 1, &l_viewport);

	VkRect2D l_scissor{};
	l_scissor.offset = { 0,0 };
	l_scissor.extent = a_swapChain->CastVulkan()->GetSwapChainExtent();
	vkCmdSetScissor(a_commandBuffer, 0, 1, &l_scissor);

	VkBuffer l_vertexBuffers[] = { a_buffer->CastVulkan()->GetVertexBuffer() };
	VkDeviceSize l_offsets[] = { 0 };
	vkCmdBindVertexBuffers(a_commandBuffer, 0, 1, l_vertexBuffers, l_offsets);

	vkCmdBindIndexBuffer(a_commandBuffer, a_buffer->CastVulkan()->GetIndexBuffer(), 0, VK_INDEX_TYPE_UINT32);


	vkCmdBindDescriptorSets(a_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, a_pipelineLayout, 0, 1, &a_descriptor->CastVulkan()->GetDescriptorSet()[currentFrame], 0, nullptr);


	vkCmdDrawIndexed(a_commandBuffer, static_cast<uint32_t>(a_model->CastVulkan()->GetIndices().size()), 1, 0, 0, 0);

	vkCmdEndRenderPass(a_commandBuffer);


	VkResult result = vkEndCommandBuffer(a_commandBuffer);
	if (result != VK_SUCCESS) {
		throw std::runtime_error("Failed to stop recording a command buffer ");
	}

}
