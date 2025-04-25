#pragma once

#include <functional>

#include "IRenderer.hpp"

#include "Core/GLFW/GLFWWindow.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"

class IFrameBuffer;

class VulkanRenderer final : public IRenderer
{
public:
    using EditorRenderCallback = std::function<void()>;
    static void RegisterEditorRenderCallback(EditorRenderCallback a_callback);

    void DrawFrame(IWindow* a_window, IDevice* a_device, ISwapChain* a_swapChain, IPipeline* a_pipeline, IBuffer* a_buffer, IRenderPassManager* a_renderPassManager, IDescriptor* a_descriptor, IMesh* a_mesh, ISynchronization* a_synchronization, ICommandBuffer* a_commandBuffer, IFrameBufferManager* a_frameBufferManager, IDepthResource* a_depthResource, ISurface* a_surface, IMultiSampling* a_multisampling) override;
    void Destroy() override {};
    VulkanRenderer* CastVulkan() override { return this; }

	void RecordCommandBuffer(const VkCommandBuffer& a_commandBuffer, const VkPipeline& a_graphicsPipeline, const VkPipelineLayout& a_pipelineLayout, const uint32_t& a_imageIndex, ISwapChain* a_swapChain, const IRenderPassManager* a_renderPassManager, IBuffer* a_buffer, IDescriptor* a_descriptor, IMesh* a_mesh, IFrameBufferManager* a_frameBufferManager) const;

	static void UpdateUniformBuffer(const uint32_t& a_currentImage, ISwapChain* a_swapChain, IBuffer* a_buffer);
	void RecreateSwapChain(IWindow* a_window, IDevice* a_device, ISurface* a_surface, ISwapChain* a_swapChain, IDepthResource* a_depthResource, IFrameBuffer* a_frameBuffer, IRenderPass* a_renderPass, IMultiSampling* a_multisampling);
	static void CleanupSwapChain(IDevice* a_device, ISwapChain* a_swapChain, IDepthResource* a_depthResource, IFrameBuffer* a_framebuffer);
	static void CreateImageViews(IDevice* a_device, ISwapChain* a_swapChain);

	[[nodiscard]] uint32_t GetCurrentFrame() const { return m_currentFrame; }

	void CreateViewportImage(IDevice* a_device, ISwapChain* a_swapchain);
    void CopyImageToViewport(ISwapChain* a_swapChain, const VkCommandBuffer& a_cmdBuffer) const;
    void DestroyViewportImage(IDevice* a_device);

	VkImage m_viewportImage;
    VkImageView m_viewportImageview;
    VkDeviceMemory m_viewportMemory;
    VkSampler m_viewportSampler;

private:
    void SetupSubmitInfo(VkSubmitInfo& a_submitInfo, const std::vector<VkSemaphore>& a_waitSemaphores, const std::array<VkPipelineStageFlags, 1>& a_waitStages, const std::vector<VkCommandBuffer>& a_commandBuffer, const std::vector<VkSemaphore>& a_signalSemaphores) const;
    static void PresentRendererInfo(VkPresentInfoKHR& a_presentInfo, const std::vector<VkSemaphore>& a_signalSemaphores, const std::vector<VkSwapchainKHR>& a_swapchains);
    static void PresentRenderPassInfo(VkRenderPassBeginInfo& a_renderPassBeginInfo, const VkRenderPass& a_renderPass, const VkFramebuffer& a_framebuffer, const VkExtent2D& a_swapchainExtent, std::array<VkClearValue, 2> a_clearValues, const bool& isEditor);
    static void FillViewportInfo(VkViewport& a_viewport, const VkExtent2D& a_swapChainExtent);

	bool m_framebufferResized { false };
	uint32_t m_currentFrame { 0 };
};
