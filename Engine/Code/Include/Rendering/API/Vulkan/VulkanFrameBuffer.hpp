#pragma once
#include "IFrameBuffer.hpp"
#include <vulkan/vulkan.hpp>
#include "Rendering/API/Vulkan/VulkanDevice.hpp"
#include "Rendering/API/Vulkan/VulkanSwapChain.hpp"
#include "Rendering/API/Vulkan/VulkanRenderPass.hpp"
#include "Rendering/API/Vulkan/VulkanDepthRessource.hpp"



class VulkanFrameBuffer : public IFrameBuffer {

public:
	void Create(IDevice* a_device, ISwapChain* a_swapChain, IRenderPass* a_renderPass, IDepthRessource* a_depthRessource) override;
	void Destroy() override;

	

private:
};