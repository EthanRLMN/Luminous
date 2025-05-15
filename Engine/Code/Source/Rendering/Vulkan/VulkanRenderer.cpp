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
#include "Rendering/Vulkan/VulkanTexture.hpp"

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

#include "Game/Systems/Time.inl"
#include "Game/Systems/Component/ModelComponent.hpp"
#include "Game/Systems/Component/RigidbodyComponent.hpp"
#include "Game/Systems/Entity/EntityManager.hpp"

#include "Matrix4.hpp"
#include <array>


void VulkanRenderer::Create(IDevice* a_device, ISwapChain* a_swapChain)
{
    m_cameraEditor.Init(static_cast<float>(a_swapChain->CastVulkan()->GetSwapChainExtent().width) / static_cast<float>(a_swapChain->CastVulkan()->GetSwapChainExtent().height),60.f, 0.1f, 100.f);
    CreateDefaultTextureSampler(a_device);


    LightComponent l_light = LightComponent();
    LightComponent l_light2 = LightComponent();
    l_light2.GetLight().m_color = Maths::Vector3(0.0f, 0.0f, 1.0f);
    l_light2.GetLight().m_type = 1;
    l_light2.GetLight().m_intensity = 0.0f;
    m_lights[1] = l_light2;

}

void VulkanRenderer::DrawFrame(IWindow* a_window, IDevice* a_device, ISwapChain* a_swapChain, IPipeline* a_pipeline, IBuffer* a_buffer, IRenderPassManager* a_renderPassManager, IDescriptor* a_descriptor, ISynchronization* a_synchronization, ICommandBuffer* a_commandBuffer, IFrameBufferManager* a_frameBufferManager, IDepthResource* a_depthResource, ISurface* a_surface, IMultiSampling* a_multisampling, IInputManager* a_inputManager, EntityManager a_entityManager)
{
    const VkDevice& l_device{ a_device->CastVulkan()->GetDevice() };
    const VkSwapchainKHR& l_swapchain{ a_swapChain->CastVulkan()->GetSwapChain() };

    vkWaitForFences(l_device, 1, &a_synchronization->CastVulkan()->GetFences()[m_currentFrame], VK_TRUE, UINT64_MAX);
    uint32_t l_imageIndex{ 0 };

    VkResult l_result = vkAcquireNextImageKHR(l_device, l_swapchain, UINT64_MAX, a_synchronization->CastVulkan()->GetImageAvailableSemaphores()[m_currentFrame], nullptr, &l_imageIndex);
    if (l_result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        RecreateSwapChain(a_window, a_device, a_surface, a_swapChain, a_depthResource, a_frameBufferManager, a_renderPassManager, a_multisampling);
        return;
    }
    if (l_result != VK_SUCCESS && l_result != VK_SUBOPTIMAL_KHR)
        throw std::runtime_error("failed to present swap chain image");

    
    m_cameraEditor.Update(static_cast<float>(a_swapChain->CastVulkan()->GetSwapChainExtent().width) / static_cast<float>(a_swapChain->CastVulkan()->GetSwapChainExtent().height));
    m_cameraEditor.UpdateInput(a_inputManager);

    UpdateUniformBuffer(m_currentFrame, a_buffer,a_entityManager);
    vkResetFences(l_device, 1, &a_synchronization->CastVulkan()->GetFences()[m_currentFrame]);

    VkSubmitInfo l_submitInfo{ };
    l_submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    l_submitInfo.pNext = nullptr;

    const std::vector<VkSemaphore> l_waitSemaphores = { a_synchronization->CastVulkan()->GetImageAvailableSemaphores()[m_currentFrame] };
    const std::array<VkPipelineStageFlags, 1> l_waitStages = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    const std::vector<VkSemaphore> l_signalSemaphores = { a_synchronization->CastVulkan()->GetRenderFinishedSemaphores()[m_currentFrame] };
    SetupSubmitInfo(l_submitInfo, l_waitSemaphores, l_waitStages, a_commandBuffer->CastVulkan()->GetCommandBuffers(), l_signalSemaphores);

    vkResetCommandBuffer(a_commandBuffer->CastVulkan()->GetCommandBuffers()[m_currentFrame], 0);
    RecordCommandBuffer(a_commandBuffer->CastVulkan()->GetCommandBuffers()[m_currentFrame], a_pipeline->CastVulkan()->GetGraphicsPipeline(), a_pipeline->CastVulkan()->GetPipelineLayout(), l_imageIndex, a_swapChain, a_renderPassManager, a_descriptor, a_frameBufferManager, a_entityManager, a_pipeline->CastVulkan()->GetWireframeGraphicsPipeline());

    if (vkQueueSubmit(a_device->CastVulkan()->GetGraphicsQueue(), 1, &l_submitInfo, a_synchronization->CastVulkan()->GetFences()[m_currentFrame]) != VK_SUCCESS)
        DEBUG_LOG_ERROR("Failed to submit draw command buffer");

    VkPresentInfoKHR l_presentInfo{ };
    l_presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    l_presentInfo.pNext = nullptr;

    const std::vector<VkSwapchainKHR> l_swapChains = { l_swapchain };
    PresentRendererInfo(l_presentInfo, l_signalSemaphores, l_swapChains);
    l_presentInfo.pImageIndices = &l_imageIndex;

    l_result = vkQueuePresentKHR(a_device->CastVulkan()->GetPresentationQueue(), &l_presentInfo);
    if (l_result == VK_ERROR_OUT_OF_DATE_KHR || l_result == VK_SUBOPTIMAL_KHR)
    {
        DEBUG_LOG_ERROR("failed to present swap chain image");
        this->SetViewportSize(0, 0);
        RecreateSwapChain(a_window, a_device, a_surface, a_swapChain, a_depthResource, a_frameBufferManager, a_renderPassManager, a_multisampling);
    }
    else if (l_result != VK_SUCCESS)
        DEBUG_LOG_ERROR("failed to present swap chain image");

    m_currentFrame = (m_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}


void VulkanRenderer::RecordCommandBuffer(const VkCommandBuffer& a_commandBuffer, const VkPipeline& a_graphicsPipeline, const VkPipelineLayout& a_pipelineLayout, const uint32_t& a_imageIndex, ISwapChain* a_swapChain, const IRenderPassManager* a_renderPassManager, IDescriptor* a_descriptor, const IFrameBufferManager* a_frameBufferManager, const EntityManager& a_entityManager, const VkPipeline& a_wireGraphicsPipeline) const
{
    VkCommandBufferBeginInfo l_bufferBeginInfo { };
    l_bufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    l_bufferBeginInfo.pNext = nullptr;

    if (vkBeginCommandBuffer(a_commandBuffer, &l_bufferBeginInfo) != VK_SUCCESS)
        DEBUG_LOG_INFO("failed to begin recording command buffer!\n");

    for (IRenderPass* l_renderPass : a_renderPassManager->GetRenderPasses())
    {
        VkRenderPassBeginInfo l_renderPassBeginInfo { };
        l_renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        l_renderPassBeginInfo.pNext = nullptr;

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

            // Draw all the ModelComponents in the Scene
            std::vector<std::shared_ptr<Entity>> entitiesWithModels = a_entityManager.GetEntitiesByComponent<ModelComponent>();

            for (const std::shared_ptr<Entity>& entity : entitiesWithModels)
            {
                //Set Ubo's values
                UniformBufferObject l_ubo{};
                const Maths::Matrix4 l_modelMatrix = entity->Transform()->GetGlobalMatrix();
                l_ubo.model = l_modelMatrix.Transpose();
                l_ubo.view = m_cameraEditor.GetViewMatrix().Transpose();
                l_ubo.proj = m_cameraEditor.GetProjectionMatrix();
                l_ubo.debug = 0; // Debug = 0 : Light applied to it (Most models)

                //Send the ubo and Draw the Model 
                DrawModel(entity->GetComponent<ModelComponent>().get(), a_commandBuffer, a_descriptor, a_graphicsPipeline, a_pipelineLayout, l_ubo);

            }


            // Draw all the Colliders in the Scene (Editor only Debug)
            std::vector<std::shared_ptr<Entity>> entitieswithColliders = a_entityManager.GetEntitiesByComponent<RigidbodyComponent>();

            vkCmdBindPipeline(a_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, a_wireGraphicsPipeline);

            for (const std::shared_ptr<Entity>& entity : entitieswithColliders)
            {

                //Set Ubo's Camera (View/Projection)
                UniformBufferObject l_ubo{};
                l_ubo.view = m_cameraEditor.GetViewMatrix().Transpose();
                l_ubo.proj = m_cameraEditor.GetProjectionMatrix();
                l_ubo.debug = 1; //Debug = 1 : No lights applied (Used to debug colliders)

                //Get Basic Components
                TransformComponent* l_transform = entity->Transform().get();
                RigidbodyComponent* l_rigidbody = entity->GetComponent<RigidbodyComponent>().get();
                ColliderType l_colliderType = l_rigidbody->GetColliderType();

                Maths::Vector3 l_pos = l_transform->GetGlobalPosition();
                Maths::Vector3 l_rot = l_transform->GetGlobalRotationVec();
                Maths::Vector3 l_scale = l_transform->GetGlobalScale();

                //Check the collider type
                if (l_colliderType == ColliderType::SPHERECOLLIDER)
                {
                    float l_radius = l_scale.y += l_rigidbody->GetSphereOffset();
                    l_scale = Maths::Vector3(l_radius);

                    //Matrix recalculation to fit sphere size's norm
                    Maths::Matrix4 l_posMat = Maths::Matrix4::Translation(l_pos);
                    Maths::Matrix4 l_rotMat = Maths::Matrix4::RotationXYZ(l_rot);
                    Maths::Matrix4 l_scaleMat = Maths::Matrix4::Scale(l_scale);
                    Maths::Matrix4 l_modelMatrixSphere = Maths::Matrix4::TRS(l_posMat, l_rotMat, l_scaleMat);

                    l_ubo.model = l_modelMatrixSphere.Transpose();
                }
                else if (l_colliderType == ColliderType::CAPSULECOLLIDER)
                {
                    //Get basic collider's values
                    float l_capsuleRadius = l_rigidbody->GetCapsuleWidth();
                    float l_capsuleHeight = l_rigidbody->GetCapsuleHeight();
                    Maths::Vector2 l_capsuleSizeOffset = l_rigidbody->GetCapsuleOffset();

                    Maths::Quaternion l_rotQuat = l_transform->GetGlobalRotationQuat();
                    Maths::Quaternion l_rotQuatOpposite = Maths::Quaternion(-l_rotQuat.x, -l_rotQuat.y, -l_rotQuat.z, l_rotQuat.w); //Rotation is the opposite on Jolt : need to reverse the quat rotation
                    l_rot = l_rotQuatOpposite.ToEulerAngles(true);
                    Maths::Vector3 l_scale = l_transform->GetGlobalScale();
                    l_scale = Maths::Vector3(l_capsuleRadius + l_capsuleSizeOffset.x);

                    Maths::Matrix4 l_rotMat = Maths::Matrix4::RotationXYZ(l_rot);
                    Maths::Matrix4 l_scaleMat = Maths::Matrix4::Scale(l_scale);

                    //Loop 2 times to draw both tips of the cynlinder (spheres)
                    for (int l_i = 0; l_i < 2; ++l_i)
                    {
                        //Calculate offset to position the spheres right
                        Maths::Vector3 l_add = Maths::Vector3(0, l_capsuleHeight + l_capsuleSizeOffset.y, 0) * l_rotQuat;
                        if (l_i == 0)
                            l_pos += l_add;
                        else
                            l_pos -= l_add;

                        Maths::Matrix4 l_posMat = Maths::Matrix4::Translation(l_pos);

                        Maths::Matrix4 l_modelMatrixSphere = Maths::Matrix4::TRS(l_posMat, l_rotMat, l_scaleMat);
                        l_ubo.model = l_modelMatrixSphere.Transpose();

                        DrawModel(l_rigidbody->GetCapsuleSphereDebug(), a_commandBuffer, a_descriptor, a_graphicsPipeline, a_pipelineLayout, l_ubo);
                        l_pos = l_transform->GetGlobalPosition();
                    }

                    //Setting the values back for the cylinder
                    l_scale = Maths::Vector3(l_capsuleRadius + l_capsuleSizeOffset.x, l_capsuleHeight + l_capsuleSizeOffset.y, l_capsuleRadius + l_capsuleSizeOffset.x);

                    Maths::Matrix4 l_posMat = Maths::Matrix4::Translation(l_pos);
                    l_rotMat = Maths::Matrix4::RotationXYZ(l_rot);
                    l_scaleMat = Maths::Matrix4::Scale(l_scale);
                    Maths::Matrix4 l_modelMatrixSphere = Maths::Matrix4::TRS(l_posMat, l_rotMat, l_scaleMat);

                    l_ubo.model = l_modelMatrixSphere.Transpose();
                }
                else if (l_colliderType == ColliderType::BOXCOLLIDER)
                {
                    l_scale += l_rigidbody->GetBoxOffset();

                    Maths::Matrix4 l_posMat = Maths::Matrix4::Translation(l_pos);
                    Maths::Matrix4 l_rotMat = Maths::Matrix4::RotationXYZ(l_rot);
                    Maths::Matrix4 l_scaleMat = Maths::Matrix4::Scale(l_scale);
                    Maths::Matrix4 l_modelMatrixSphere = Maths::Matrix4::TRS(l_posMat, l_rotMat, l_scaleMat);
                    l_ubo.model = l_modelMatrixSphere.Transpose();
                }
                //Draw the basic shape (sphere,box,cynlinder)
                DrawModel(entity.get()->GetComponent<RigidbodyComponent>().get()->GetModelDebug(), a_commandBuffer, a_descriptor, a_graphicsPipeline, a_pipelineLayout, l_ubo);

            }
            vkCmdBindPipeline(a_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, a_graphicsPipeline);
        }

        // Callback ImGui_ImplVulkan_RenderDrawData
        if (l_renderPass == a_renderPassManager->GetRenderPassAt(1))
            if (s_editorGuiCallback)
                s_editorGuiCallback();

        

        vkCmdEndRenderPass(a_commandBuffer);
        
        if (l_renderPass == a_renderPassManager->GetRenderPassAt(0))
        {
            CopyImageToViewport(a_swapChain, a_commandBuffer);           
        } 
    }

    const VkResult l_result = vkEndCommandBuffer(a_commandBuffer);
    if (l_result != VK_SUCCESS)
        throw std::runtime_error("Failed to stop recording a command buffer ");
}

void VulkanRenderer::DrawModel(ModelComponent* a_model, const VkCommandBuffer& a_commandBuffer, IDescriptor* a_descriptor, const VkPipeline& a_graphicsPipeline, const VkPipelineLayout& a_pipelineLayout, UniformBufferObject a_ubo) const
{
    VulkanMesh* l_mesh = a_model->GetMesh()->CastVulkan();
    VulkanTexture* l_texture = a_model->GetTexture()->CastVulkan();

    const std::array<VkBuffer, 1> l_vertexBuffers = { l_mesh->GetVertexBuffer() };
    const std::array<VkDeviceSize, 1> l_offsets = { 0 };
    vkCmdBindVertexBuffers(a_commandBuffer, 0, 1, l_vertexBuffers.data(), l_offsets.data());
    vkCmdBindIndexBuffer(a_commandBuffer, l_mesh->GetIndexBuffer(), 0, VK_INDEX_TYPE_UINT32);
    std::vector<VkDescriptorSet> sets = { a_descriptor->CastVulkan()->GetDescriptorSet()[m_currentFrame], l_texture->GetDescriptorSet() };
    vkCmdBindDescriptorSets(a_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, a_pipelineLayout, 0, static_cast<uint32_t>(sets.size()), sets.data(), 0, nullptr);
    vkCmdPushConstants(a_commandBuffer, a_pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(UniformBufferObject), &a_ubo);
    vkCmdDrawIndexed(a_commandBuffer, static_cast<uint32_t>(l_mesh->GetIndices().size()), 1, 0, 0, 0);
}


void VulkanRenderer::UpdateUniformBuffer(const uint32_t& a_currentFrame, IBuffer* a_buffer, const EntityManager& a_entityManager) const
{
    a_entityManager.Update();

    memcpy(a_buffer->CastVulkan()->GetLightUniformBuffersMapped()[a_currentFrame], const_cast<void*>(static_cast<const void*>(&m_lights)), sizeof(LightData) * MAX_LIGHTS);
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
    a_swapChain->CastVulkan()->Create(a_window, a_device, a_surface);
    
    CreateViewportImage(a_device, a_swapChain);
    bReloadImage = true;
    
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
    const VkExtent2D& l_extent = a_swapChain->CastVulkan()->GetSwapChainExtent();
    SetViewportSize(static_cast<float>(l_extent.width), static_cast<float> (l_extent.height));

    if (m_viewportImage != VK_NULL_HANDLE && m_viewportImageview != VK_NULL_HANDLE && m_viewportMemory != VK_NULL_HANDLE)
        DestroyViewportImage(a_device);

    CreateViewportImageInfo(a_device->CastVulkan()->GetDevice(), a_swapChain->CastVulkan()->GetSwapChainImageFormat());

    VkMemoryRequirements l_memRequirements;
    vkGetImageMemoryRequirements(l_device, m_viewportImage, &l_memRequirements);

    VkMemoryAllocateInfo l_allocInfo{ };
    l_allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    l_allocInfo.allocationSize = l_memRequirements.size;
    l_allocInfo.memoryTypeIndex = VulkanSwapChain::FindMemoryType(a_device->CastVulkan()->GetPhysicalDevice(), l_memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    l_allocInfo.pNext = nullptr;
    vkAllocateMemory(l_device, &l_allocInfo, nullptr, &m_viewportMemory);
    vkBindImageMemory(l_device, m_viewportImage, m_viewportMemory, 0);

    VkImageViewCreateInfo l_viewInfo{ };
    ImageViewCreateInfo(l_viewInfo, m_viewportImage, a_swapChain);
    vkCreateImageView(l_device, &l_viewInfo, nullptr, &m_viewportImageview);

    VkSamplerCreateInfo l_samplerInfo{ };
    SamplerCreateInfo(l_samplerInfo);
    vkCreateSampler(l_device, &l_samplerInfo, nullptr, &m_viewportSampler);
}



void VulkanRenderer::CopyImageToViewport(ISwapChain* a_swapChain, const VkCommandBuffer& a_cmdBuffer) const
{
    VkImageMemoryBarrier l_barrierSrc{ };
    ImageMemoryBarrierSrc(l_barrierSrc,a_swapChain,m_currentFrame);
    vkCmdPipelineBarrier(a_cmdBuffer, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &l_barrierSrc);

    VkImageMemoryBarrier l_barrierDst{ };
    ImageMemoryBarrierDst(l_barrierDst, m_viewportImage);
    vkCmdPipelineBarrier(a_cmdBuffer, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &l_barrierDst);

    VkImageCopy l_copyRegion{};
    ImageCopyRegion(l_copyRegion,m_viewportWidth,m_viewportHeight);
    vkCmdCopyImage(a_cmdBuffer, a_swapChain->CastVulkan()->GetSwapChainImages()[m_currentFrame], VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, m_viewportImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &l_copyRegion);

    VkImageMemoryBarrier l_barrierFinal{ };
    ImageMemoryBarrierFinal(l_barrierFinal, m_viewportImage);
    vkCmdPipelineBarrier(a_cmdBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, nullptr, 0, nullptr, 1, &l_barrierFinal);
}


void VulkanRenderer::DestroyViewportImage(IDevice* a_device)
{
    const VkDevice& l_device = a_device->CastVulkan()->GetDevice();
    if (m_viewportImageview != VK_NULL_HANDLE)
    {
        vkDestroyImageView(l_device, m_viewportImageview, nullptr);
        m_viewportImageview = VK_NULL_HANDLE;
    }

    if (m_viewportImage != VK_NULL_HANDLE)
    {
        vkDestroyImage(l_device, m_viewportImage, nullptr);
        m_viewportImage = VK_NULL_HANDLE;
    }

    if (m_viewportSampler != VK_NULL_HANDLE)
    {
        vkDestroySampler(l_device, m_viewportSampler, nullptr);
        m_viewportSampler = VK_NULL_HANDLE;
    }

    if (m_viewportMemory != VK_NULL_HANDLE)
    {
        vkFreeMemory(l_device, m_viewportMemory, nullptr);
        m_viewportMemory = VK_NULL_HANDLE;
    }

    if (m_defaultTexSampler != nullptr)
    {
        vkDestroySampler(l_device, m_defaultTexSampler, nullptr);
        DEBUG_LOG_INFO("Default texture sampler has been destroyed.");
    }

}

void VulkanRenderer::CreateDefaultTextureSampler(IDevice* a_device)
{
    VkSamplerCreateInfo l_samplerInfo{ };
    l_samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    l_samplerInfo.magFilter = VK_FILTER_LINEAR;
    l_samplerInfo.minFilter = VK_FILTER_LINEAR;
    l_samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    l_samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    l_samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    l_samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    l_samplerInfo.anisotropyEnable = VK_FALSE;
    l_samplerInfo.maxAnisotropy = 1.0f;
    l_samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    l_samplerInfo.unnormalizedCoordinates = VK_FALSE;
    l_samplerInfo.compareEnable = VK_FALSE;
    l_samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
    l_samplerInfo.mipLodBias = 0.0f;
    l_samplerInfo.minLod = 0.0f;
    l_samplerInfo.maxLod = VK_LOD_CLAMP_NONE;
    l_samplerInfo.pNext = nullptr;

    vkCreateSampler(a_device->CastVulkan()->GetDevice(), &l_samplerInfo, nullptr, &m_defaultTexSampler);
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
    const float l_width = static_cast<float>(a_swapChainExtent.width);
    const float l_height = static_cast<float>(a_swapChainExtent.height);

    a_viewport.x = 0.0f;
    a_viewport.y = l_height;
    a_viewport.width = l_width;
    a_viewport.height = -l_height;
    a_viewport.minDepth = 0.0f;
    a_viewport.maxDepth = 1.0f;
}

VkResult VulkanRenderer::CreateViewportImageInfo(const VkDevice& a_device, const VkFormat& a_swapchainImageFormat)
{
    VkImageCreateInfo l_imageInfo {};

    l_imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    l_imageInfo.imageType = VK_IMAGE_TYPE_2D;
    l_imageInfo.extent.width = static_cast<uint32_t>(m_viewportWidth);
    l_imageInfo.extent.height = static_cast<uint32_t>(m_viewportHeight);
    l_imageInfo.extent.depth = 1;
    l_imageInfo.mipLevels = 1;
    l_imageInfo.arrayLayers = 1;
    l_imageInfo.format = a_swapchainImageFormat;
    l_imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    l_imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    l_imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    l_imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    l_imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    l_imageInfo.flags = 0;
    l_imageInfo.pNext = nullptr;

    return vkCreateImage(a_device, &l_imageInfo, nullptr, &m_viewportImage);
}

void VulkanRenderer::ImageViewCreateInfo(VkImageViewCreateInfo& a_viewInfo, const VkImage& a_vkImage, ISwapChain* a_swapChain)
{
    a_viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    a_viewInfo.image = a_vkImage;
    a_viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    a_viewInfo.format = a_swapChain->CastVulkan()->GetSwapChainImageFormat();
    a_viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    a_viewInfo.subresourceRange.baseMipLevel = 0;
    a_viewInfo.subresourceRange.levelCount = 1;
    a_viewInfo.subresourceRange.baseArrayLayer = 0;
    a_viewInfo.subresourceRange.layerCount = 1;
    a_viewInfo.pNext = nullptr;
}

void VulkanRenderer::SamplerCreateInfo(VkSamplerCreateInfo& a_samplerInfo)
{
    a_samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    a_samplerInfo.magFilter = VK_FILTER_LINEAR;
    a_samplerInfo.minFilter = VK_FILTER_LINEAR;
    a_samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    a_samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    a_samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    a_samplerInfo.anisotropyEnable = VK_FALSE;
    a_samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    a_samplerInfo.unnormalizedCoordinates = VK_FALSE;
    a_samplerInfo.compareEnable = VK_FALSE;
    a_samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    a_samplerInfo.pNext = nullptr;
}

void VulkanRenderer::ImageMemoryBarrierSrc(VkImageMemoryBarrier& a_barrierSrc, ISwapChain* a_swapChain, uint32_t a_currentFrame)
{
    a_barrierSrc.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    a_barrierSrc.oldLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    a_barrierSrc.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    a_barrierSrc.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    a_barrierSrc.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
    a_barrierSrc.image = a_swapChain->CastVulkan()->GetSwapChainImages()[a_currentFrame];
    a_barrierSrc.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
    a_barrierSrc.pNext = nullptr;
}

void VulkanRenderer::ImageMemoryBarrierDst(VkImageMemoryBarrier& a_barrierDst, const VkImage& a_vkImage)
{
    a_barrierDst.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    a_barrierDst.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    a_barrierDst.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    a_barrierDst.srcAccessMask = 0;
    a_barrierDst.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    a_barrierDst.image = a_vkImage;
    a_barrierDst.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
    a_barrierDst.pNext = nullptr;
}

void VulkanRenderer::ImageCopyRegion(VkImageCopy& a_copyRegion,float a_viewportWidth,float a_viewportHeight)
{
    a_copyRegion.srcSubresource = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };
    a_copyRegion.dstSubresource = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };
    a_copyRegion.extent.width = static_cast<uint32_t>(a_viewportWidth);
    a_copyRegion.extent.height = static_cast<uint32_t>(a_viewportHeight);
    a_copyRegion.extent.depth = 1;
}

void VulkanRenderer::ImageMemoryBarrierFinal(VkImageMemoryBarrier& a_barrierFinal, const VkImage& a_vkImage)
{
    a_barrierFinal.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    a_barrierFinal.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    a_barrierFinal.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    a_barrierFinal.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    a_barrierFinal.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    a_barrierFinal.image = a_vkImage;
    a_barrierFinal.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
    a_barrierFinal.pNext = nullptr;
}
