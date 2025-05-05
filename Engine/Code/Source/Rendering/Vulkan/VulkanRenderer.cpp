#include "ICommandBuffer.hpp"
#include "IDepthResource.hpp"
#include "IDescriptor.hpp"
#include "IFrameBuffer.hpp"
#include "IFrameBufferManager.hpp"
#include "IMesh.hpp"
#include "IPipeline.hpp"
#include "IRenderPassManager.hpp"
#include "ISwapChain.hpp"
#include "ISynchronization.hpp"

#include "Rendering/Vulkan/VulkanRenderer.hpp"
#include "Rendering/Vulkan/VulkanBuffer.hpp"
#include "Rendering/Vulkan/VulkanCommandBuffer.hpp"
#include "Rendering/Vulkan/VulkanDepthResource.hpp"
#include "Rendering/Vulkan/VulkanDescriptor.hpp"
#include "Rendering/Vulkan/VulkanFrameBuffer.hpp"
#include "Rendering/Vulkan/VulkanMesh.hpp"
#include "Rendering/Vulkan/VulkanMultiSampling.hpp"
#include "Rendering/Vulkan/VulkanPipeline.hpp"
#include "Rendering/Vulkan/VulkanRenderPass.hpp"
#include "Rendering/Vulkan/VulkanSwapChain.hpp"
#include "Rendering/Vulkan/VulkanSynchronization.hpp"

#include "Matrix4.hpp"
#include "Game/Systems/Time.inl"


void VulkanRenderer::Create(IWindow* a_window, ISwapChain* a_swapChain)
{
    m_cameraEditor.Init(a_window, static_cast<float>(a_swapChain->CastVulkan()->GetSwapChainExtent().width) / static_cast<float>(a_swapChain->CastVulkan()->GetSwapChainExtent().height),45.f,0.01f,1000.f);


    LightComponent l_light = LightComponent();
    m_lights.push_back(l_light);

    m_light = LightComponent();
}

void VulkanRenderer::DrawFrame(IWindow* a_window, IDevice* a_device, ISwapChain* a_swapChain, IPipeline* a_pipeline, IBuffer* a_buffer, IRenderPassManager* a_renderPassManager, IDescriptor* a_descriptor, IMesh* a_mesh, ISynchronization* a_synchronization, ICommandBuffer* a_commandBuffer, IFrameBufferManager* a_frameBufferManager, IDepthResource* a_depthResource, ISurface* a_surface, IMultiSampling* a_multisampling,IInputManager* a_inputManager)
{
    const VkDevice& l_device{ a_device->CastVulkan()->GetDevice() };
    const VkSwapchainKHR& l_swapchain{ a_swapChain->CastVulkan()->GetSwapChain() };

    vkWaitForFences(l_device, 1, &a_synchronization->CastVulkan()->GetFences()[m_currentFrame], VK_TRUE, UINT64_MAX);
    uint32_t l_imageIndex{ 0 };
    

    if (a_inputManager->CastGLFW()->IsKeyDown(a_window, Key::KEY_RIGHT))
    {
        m_lights[0].m_position += Maths::Vector3(0.01f, 0, 0);
    }
    if (a_inputManager->CastGLFW()->IsKeyDown(a_window, Key::KEY_LEFT))
    {
        m_lights[0].m_position -= Maths::Vector3(0.01f, 0, 0);
    }
    if (a_inputManager->CastGLFW()->IsKeyDown(a_window, Key::KEY_UP))
    {
        m_lights[0].m_position += Maths::Vector3(0, 0.01f, 0);
    }
    if (a_inputManager->CastGLFW()->IsKeyDown(a_window, Key::KEY_DOWN))
    {
        m_lights[0].m_position -= Maths::Vector3(0, 0.01f, 0);
    }

    VkResult l_result = vkAcquireNextImageKHR(l_device, l_swapchain, UINT64_MAX, a_synchronization->CastVulkan()->GetImageAvailableSemaphores()[m_currentFrame], nullptr, &l_imageIndex);
    if (l_result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        RecreateSwapChain(a_window, a_device, a_surface, a_swapChain, a_depthResource, a_frameBufferManager, a_renderPassManager, a_multisampling);
        return;
    }
    if (l_result != VK_SUCCESS && l_result != VK_SUBOPTIMAL_KHR)
        throw std::runtime_error("failed to present swap chain image");

    //***********************************//
    //OLD Camera Settings Here
    
    m_cameraEditor.Update(static_cast<float>(a_swapChain->CastVulkan()->GetSwapChainExtent().width) / static_cast<float>(a_swapChain->CastVulkan()->GetSwapChainExtent().height));
    m_cameraEditor.UpdateInput(a_window,a_inputManager);

    ///*************************************************//


    UpdateUniformBuffer(l_device,m_currentFrame, a_buffer);
    vkResetFences(l_device, 1, &a_synchronization->CastVulkan()->GetFences()[m_currentFrame]);

    VkSubmitInfo l_submitInfo{ VK_STRUCTURE_TYPE_SUBMIT_INFO };
    const std::vector<VkSemaphore> l_waitSemaphores = { a_synchronization->CastVulkan()->GetImageAvailableSemaphores()[m_currentFrame] };
    const std::array<VkPipelineStageFlags, 1> l_waitStages = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    const std::vector<VkSemaphore> l_signalSemaphores = { a_synchronization->CastVulkan()->GetRenderFinishedSemaphores()[m_currentFrame] };
    SetupSubmitInfo(l_submitInfo, l_waitSemaphores, l_waitStages, a_commandBuffer->CastVulkan()->GetCommandBuffers(), l_signalSemaphores);

    vkResetCommandBuffer(a_commandBuffer->CastVulkan()->GetCommandBuffers()[m_currentFrame], 0);
    RecordCommandBuffer(a_commandBuffer->CastVulkan()->GetCommandBuffers()[m_currentFrame], a_pipeline->CastVulkan()->GetGraphicsPipeline(), a_pipeline->CastVulkan()->GetPipelineLayout(), l_imageIndex, a_swapChain, a_renderPassManager, a_buffer, a_descriptor, a_mesh, a_frameBufferManager);

    if (vkQueueSubmit(a_device->CastVulkan()->GetGraphicsQueue(), 1, &l_submitInfo, a_synchronization->CastVulkan()->GetFences()[m_currentFrame]) != VK_SUCCESS)
        DEBUG_LOG_ERROR("Failed to submit draw command buffer");

    VkPresentInfoKHR l_presentInfo{ VK_STRUCTURE_TYPE_PRESENT_INFO_KHR };
    const std::vector<VkSwapchainKHR> l_swapChains = { l_swapchain };
    PresentRendererInfo(l_presentInfo, l_signalSemaphores, l_swapChains);
    l_presentInfo.pImageIndices = &l_imageIndex;

    l_result = vkQueuePresentKHR(a_device->CastVulkan()->GetPresentationQueue(), &l_presentInfo);
    if (l_result == VK_ERROR_OUT_OF_DATE_KHR || l_result == VK_SUBOPTIMAL_KHR)
    {
        // DEBUG_LOG_ERROR("failed to present swap chain image");
        this->SetViewportSize(0, 0);
        RecreateSwapChain(a_window, a_device, a_surface, a_swapChain, a_depthResource, a_frameBufferManager, a_renderPassManager, a_multisampling);
    }
    else if (l_result != VK_SUCCESS)
        DEBUG_LOG_ERROR("failed to present swap chain image");

    m_currentFrame = (m_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}


void VulkanRenderer::RecordCommandBuffer(const VkCommandBuffer& a_commandBuffer, const VkPipeline& a_graphicsPipeline, const VkPipelineLayout& a_pipelineLayout, const uint32_t& a_imageIndex, ISwapChain* a_swapChain, const IRenderPassManager* a_renderPassManager, IBuffer* a_buffer, IDescriptor* a_descriptor, IMesh* a_mesh, IFrameBufferManager* a_frameBufferManager) const
{
    const VkCommandBufferBeginInfo l_bufferBeginInfo = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
    if (vkBeginCommandBuffer(a_commandBuffer, &l_bufferBeginInfo) != VK_SUCCESS)
        DEBUG_LOG_INFO("failed to begin recording command buffer!\n");

    for (IRenderPass* l_renderPass : a_renderPassManager->GetRenderPasses())
    {
        VkRenderPassBeginInfo l_renderPassBeginInfo = { VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO };
        const std::array<VkClearValue, 2> l_clearValues{};
        if (l_renderPass == a_renderPassManager->GetRenderPassAt(0))
            PresentRenderPassInfo(l_renderPassBeginInfo, l_renderPass->CastVulkan()->GetRenderPass(), a_frameBufferManager->GetFrameBufferAt(0)->CastVulkan()->GetFrameBuffers()[a_imageIndex], a_swapChain->CastVulkan()->GetSwapChainExtent(), l_clearValues);
        else
            PresentRenderPassInfo(l_renderPassBeginInfo, l_renderPass->CastVulkan()->GetRenderPass(), a_frameBufferManager->GetFrameBufferAt(1)->CastVulkan()->GetFrameBuffers()[a_imageIndex], a_swapChain->CastVulkan()->GetSwapChainExtent(), l_clearValues);

        vkCmdBeginRenderPass(a_commandBuffer, &l_renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(a_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, a_graphicsPipeline);

        VkViewport l_viewport{};
        FillViewportInfo(l_viewport, a_swapChain->CastVulkan()->GetSwapChainExtent());
        vkCmdSetViewport(a_commandBuffer, 0, 1, &l_viewport);

        const VkRect2D l_scissor{
            .offset = { 0, 0 },
            .extent = a_swapChain->CastVulkan()->GetSwapChainExtent()
        };
        vkCmdSetScissor(a_commandBuffer, 0, 1, &l_scissor);

        if (l_renderPass == a_renderPassManager->GetRenderPassAt(0))
        {
            const std::array<VkBuffer, 1> l_vertexBuffers = { a_buffer->CastVulkan()->GetVertexBuffer() };
            const std::array<VkDeviceSize, 1> l_offsets = { 0 };
            vkCmdBindVertexBuffers(a_commandBuffer, 0, 1, l_vertexBuffers.data(), l_offsets.data());
            vkCmdBindIndexBuffer(a_commandBuffer, a_buffer->CastVulkan()->GetIndexBuffer(), 0, VK_INDEX_TYPE_UINT32);
            std::vector<VkDescriptorSet> sets = { a_descriptor->CastVulkan()->GetDescriptorSet()[m_currentFrame] };
            vkCmdBindDescriptorSets(a_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, a_pipelineLayout, 0, static_cast<uint32_t>(sets.size()), sets.data(), 0, nullptr);
            vkCmdDrawIndexed(a_commandBuffer, static_cast<uint32_t>(a_mesh->CastVulkan()->GetIndices().size()), 1, 0, 0, 0);

            


        }

        // Callback ImGui_ImplVulkan_RenderDrawData
        if (l_renderPass == a_renderPassManager->GetRenderPassAt(1))
            if (s_editorGuiCallback)
                s_editorGuiCallback();

        

        vkCmdEndRenderPass(a_commandBuffer);
        
        if (l_renderPass == a_renderPassManager->GetRenderPassAt(0))
        {
            CopyImageToViewport(a_swapChain, a_commandBuffer);
            
            //bUsable = true;
        } 
    }

    const VkResult l_result = vkEndCommandBuffer(a_commandBuffer);
    if (l_result != VK_SUCCESS)
        throw std::runtime_error("Failed to stop recording a command buffer ");
}


// TODO: Cleanup
void VulkanRenderer::UpdateUniformBuffer(const VkDevice& a_device,const uint32_t& a_currentFrame, IBuffer* a_buffer) const
{
    UniformBufferObject l_ubo{};
    l_ubo.model = Maths::Matrix4::Rotate(Maths::Matrix4(1.0f), static_cast<float>(Time::GetTotalTimeElapsed()) * 00.0f, Maths::Vector3(0.0f, 0.0f, 1.0f));
    l_ubo.view = m_cameraEditor.m_viewMatrix;
    l_ubo.proj = m_cameraEditor.m_projectionMatrix;
    l_ubo.proj.mat[1][1] *= -1;

    memcpy(a_buffer->CastVulkan()->GetUniformBuffersMapped()[a_currentFrame], &l_ubo, sizeof(l_ubo));

    
    VkDeviceSize size = sizeof(LightComponent) * 32; 
    memcpy(a_buffer->CastVulkan()->GetLightUniformBuffersMapped()[a_currentFrame], &m_light, size);
    

}


void VulkanRenderer::RecreateSwapChain(IWindow* a_window, IDevice* a_device, ISurface* a_surface, ISwapChain* a_swapChain, IDepthResource* a_depthResource, const IFrameBufferManager* a_frameBuffer, const IRenderPassManager* a_renderPass, IMultiSampling* a_multisampling)
{
    int l_width, l_height{ 0 };
    a_window->CastGLFW()->GetFrameBufferSize(&l_width, &l_height);
    while (l_width == 0 || l_height == 0)
    {
        a_window->CastGLFW()->GetFrameBufferSize(&l_width, &l_height);
        a_window->CastGLFW()->ProcessEvents();
    }

    CleanupSwapChain(a_device, a_swapChain, a_depthResource, a_frameBuffer);
    a_swapChain->CastVulkan()->Create(a_window, a_device, a_surface, a_swapChain->CastVulkan()->GetMipLevel());
    
    
    CreateViewportImage(a_device, a_swapChain);

    bReloadImage = true;
    //CreateImageViews(a_device, a_swapChain);
    
    a_multisampling->CastVulkan()->CreateColorResources(a_device, a_swapChain);
    a_depthResource->CastVulkan()->Create(a_device, a_swapChain, a_renderPass->GetRenderPassAt(0));

    m_cameraEditor.SetAspectRatio(static_cast<float>(a_swapChain->CastVulkan()->GetSwapChainExtent().width) / static_cast<float>(a_swapChain->CastVulkan()->GetSwapChainExtent().height));

    
    a_frameBuffer->GetFrameBufferAt(0)->CastVulkan()->Create(a_device, a_swapChain, a_renderPass->GetRenderPassAt(0), a_depthResource, a_multisampling, false);
    

    
    
    a_frameBuffer->GetFrameBufferAt(1)->CastVulkan()->Create(a_device, a_swapChain, a_renderPass->GetRenderPassAt(1), a_depthResource, a_multisampling, true);
    
}


void VulkanRenderer::CleanupSwapChain(IDevice* a_device, ISwapChain* a_swapChain, IDepthResource* a_depthResource, const IFrameBufferManager* a_framebuffer)
{
    vkDeviceWaitIdle(a_device->CastVulkan()->GetDevice());

    for (const VkFramebuffer& l_framebuffer2 : a_framebuffer->GetFrameBufferAt(1)->CastVulkan()->GetFrameBuffers())
        vkDestroyFramebuffer(a_device->CastVulkan()->GetDevice(), l_framebuffer2, nullptr);

    for (const VkFramebuffer& l_framebuffer : a_framebuffer->GetFrameBufferAt(0)->CastVulkan()->GetFrameBuffers())
        vkDestroyFramebuffer(a_device->CastVulkan()->GetDevice(), l_framebuffer, nullptr);

    for (const VkImageView& l_imageView : a_swapChain->CastVulkan()->GetSwapChainImageViews())
        vkDestroyImageView(a_device->CastVulkan()->GetDevice(), l_imageView, nullptr);

    vkDestroyImageView(a_device->CastVulkan()->GetDevice(), a_depthResource->CastVulkan()->GetDepthImageView(), nullptr);
    vkDestroyImage(a_device->CastVulkan()->GetDevice(), a_depthResource->CastVulkan()->GetDepthImage(), nullptr);
    vkFreeMemory(a_device->CastVulkan()->GetDevice(), a_depthResource->CastVulkan()->GetDepthImageMemory(), nullptr);

    vkDestroySwapchainKHR(a_device->CastVulkan()->GetDevice(), a_swapChain->CastVulkan()->GetSwapChain(), nullptr);
}


void VulkanRenderer::CreateImageViews(IDevice* a_device, ISwapChain* a_swapChain)
{
    a_swapChain->CastVulkan()->GetSwapChainImageViews().resize(a_swapChain->CastVulkan()->GetSwapChainImages().size());

    for (uint32_t i = 0; i < a_swapChain->CastVulkan()->GetSwapChainImages().size(); ++i)
        a_swapChain->CastVulkan()->GetSwapChainImageViews()[i] = VulkanSwapChain::CreateImageView(a_swapChain->CastVulkan()->GetSwapChainImages()[i], a_device->CastVulkan()->GetDevice(), a_swapChain->CastVulkan()->GetSwapChainImageFormat(), VK_IMAGE_ASPECT_COLOR_BIT, 1);
}


void VulkanRenderer::CreateViewportImage(IDevice* a_device, ISwapChain* a_swapChain)
{
    const VkDevice& l_device = a_device->CastVulkan()->GetDevice();
    const VkExtent2D l_extent = a_swapChain->CastVulkan()->GetSwapChainExtent();

    SetViewportSize(static_cast<float>(l_extent.width), static_cast<float> (l_extent.height));

    if (m_viewportImage != VK_NULL_HANDLE && m_viewportImageview != VK_NULL_HANDLE && m_viewportMemory != VK_NULL_HANDLE) 
    {
        DestroyViewportImage(a_device);
    }


    VkImageCreateInfo imageInfo{ VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO };
    imageInfo.imageType = VK_IMAGE_TYPE_2D;
    imageInfo.extent.width = static_cast<uint32_t>(m_viewportWidth); // l_extent.width
    imageInfo.extent.height = static_cast<uint32_t>(m_viewportHeight);
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = a_swapChain->CastVulkan()->GetSwapChainImageFormat();
    imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageInfo.flags = 0;

    vkCreateImage(l_device, &imageInfo, nullptr, &m_viewportImage);

    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(l_device, m_viewportImage, &memRequirements);

    VkMemoryAllocateInfo allocInfo{ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = VulkanSwapChain::FindMemoryType(a_device->CastVulkan()->GetPhysicalDevice(), memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    vkAllocateMemory(l_device, &allocInfo, nullptr, &m_viewportMemory);
    vkBindImageMemory(l_device, m_viewportImage, m_viewportMemory, 0);

    VkImageViewCreateInfo viewInfo{ VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
    viewInfo.image = m_viewportImage;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = a_swapChain->CastVulkan()->GetSwapChainImageFormat();
    viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    vkCreateImageView(l_device, &viewInfo, nullptr, &m_viewportImageview);


    VkSamplerCreateInfo samplerInfo{ VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO };
    samplerInfo.magFilter = VK_FILTER_LINEAR;
    samplerInfo.minFilter = VK_FILTER_LINEAR;
    samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerInfo.anisotropyEnable = VK_FALSE;
    samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    samplerInfo.unnormalizedCoordinates = VK_FALSE;
    samplerInfo.compareEnable = VK_FALSE;
    samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

    vkCreateSampler(l_device, &samplerInfo, nullptr, &m_viewportSampler);
}



void VulkanRenderer::CopyImageToViewport(ISwapChain* a_swapChain, const VkCommandBuffer& a_cmdBuffer) const
{
    
   VkImageMemoryBarrier l_barrierSrc{ VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER };
    l_barrierSrc.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    l_barrierSrc.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    l_barrierSrc.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    l_barrierSrc.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
    
    l_barrierSrc.image = a_swapChain->CastVulkan()->GetSwapChainImages()[m_currentFrame];
    l_barrierSrc.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };

    vkCmdPipelineBarrier(a_cmdBuffer, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &l_barrierSrc);

    VkImageMemoryBarrier l_barrierDst{ VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER };
    l_barrierDst.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    l_barrierDst.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    l_barrierDst.srcAccessMask = 0;
    l_barrierDst.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    l_barrierDst.image = m_viewportImage;
    l_barrierDst.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };

    vkCmdPipelineBarrier(a_cmdBuffer, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &l_barrierDst);

    VkImageCopy l_copyRegion{};
    l_copyRegion.srcSubresource = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };
    l_copyRegion.dstSubresource = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };
    l_copyRegion.extent.width = static_cast<uint32_t>(m_viewportWidth);
    l_copyRegion.extent.height = static_cast<uint32_t>(m_viewportHeight);
    l_copyRegion.extent.depth = 1;

    vkCmdCopyImage(a_cmdBuffer, a_swapChain->CastVulkan()->GetSwapChainImages()[m_currentFrame], VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, m_viewportImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &l_copyRegion);

    VkImageMemoryBarrier l_barrierFinal{ VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER };
    l_barrierFinal.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    l_barrierFinal.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    l_barrierFinal.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    l_barrierFinal.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    l_barrierFinal.image = m_viewportImage;
    l_barrierFinal.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };

    vkCmdPipelineBarrier(a_cmdBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, nullptr, 0, nullptr, 1, &l_barrierFinal);
}


void VulkanRenderer::DestroyViewportImage(IDevice* a_device) const
{
    const VkDevice& l_device = a_device->CastVulkan()->GetDevice();
    if (m_viewportSampler != VK_NULL_HANDLE)
    {
        DEBUG_LOG_INFO("Viewport sampler has been destroyed.");
        vkDestroySampler(l_device, m_viewportSampler, nullptr);
    }

    if (m_viewportImageview != VK_NULL_HANDLE)
    {
        DEBUG_LOG_INFO("Viewport image view has been destroyed.");
        vkDestroyImageView(l_device, m_viewportImageview, nullptr);
    }
    
    if (m_viewportMemory != VK_NULL_HANDLE)
    {
        DEBUG_LOG_INFO("Viewport image memory has been destroyed.");
        vkFreeMemory(l_device, m_viewportMemory, nullptr);
    }

    if (m_viewportImage != VK_NULL_HANDLE)
    {
        DEBUG_LOG_INFO("Viewport image has been destroyed.");
        vkDestroyImage(l_device, m_viewportImage, nullptr);
    }

}


void VulkanRenderer::SetupSubmitInfo(VkSubmitInfo& a_submitInfo, const std::vector<VkSemaphore>& a_waitSemaphores, const std::array<VkPipelineStageFlags, 1>& a_waitStages, const std::vector<VkCommandBuffer>& a_commandBuffer, const std::vector<VkSemaphore>& a_signalSemaphores) const
{
    a_submitInfo.waitSemaphoreCount = 1;
    a_submitInfo.pWaitSemaphores = a_waitSemaphores.data();
    a_submitInfo.pWaitDstStageMask = a_waitStages.data();
    a_submitInfo.commandBufferCount = 1;
    a_submitInfo.pCommandBuffers = &a_commandBuffer[m_currentFrame];

    a_submitInfo.signalSemaphoreCount = 1;
    a_submitInfo.pSignalSemaphores = a_signalSemaphores.data();
}


void VulkanRenderer::PresentRendererInfo(VkPresentInfoKHR& a_presentInfo, const std::vector<VkSemaphore>& a_signalSemaphores, const std::vector<VkSwapchainKHR>& a_swapchains)
{
    a_presentInfo.waitSemaphoreCount = 1;
    a_presentInfo.pWaitSemaphores = a_signalSemaphores.data();

    a_presentInfo.swapchainCount = 1;
    a_presentInfo.pSwapchains = a_swapchains.data();
}


void VulkanRenderer::PresentRenderPassInfo(VkRenderPassBeginInfo& a_renderPassBeginInfo, const VkRenderPass& a_renderPass, const VkFramebuffer& a_framebuffer, const VkExtent2D& a_swapchainExtent, std::array<VkClearValue, 2> a_clearValues)
{
    a_renderPassBeginInfo.renderPass = a_renderPass;
    a_renderPassBeginInfo.framebuffer = a_framebuffer;
    a_renderPassBeginInfo.renderArea.offset = { 0, 0 };
    a_renderPassBeginInfo.renderArea.extent = a_swapchainExtent;

    a_clearValues[0].color = { { 0.1f, 0.1f, 0.1f, 1.0f } };
    a_clearValues[1].depthStencil = { 1.0f, 0 };

    a_renderPassBeginInfo.clearValueCount = static_cast<uint32_t>(a_clearValues.size());
    a_renderPassBeginInfo.pClearValues = a_clearValues.data();
}


void VulkanRenderer::FillViewportInfo(VkViewport& a_viewport, const VkExtent2D& a_swapChainExtent)
{
    a_viewport.x = 0.0f;
    a_viewport.y = 0.0f;
    a_viewport.width = static_cast<float>(a_swapChainExtent.width);
    a_viewport.height = static_cast<float>(a_swapChainExtent.height);
    a_viewport.minDepth = 0.0f;
    a_viewport.maxDepth = 1.0f;
}
