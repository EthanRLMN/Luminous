#include "ICommandBuffer.hpp"
#include <vulkan/vulkan.hpp>
#include "Struct/VulkanUtilities.hpp"
#include "Rendering/API/Vulkan/VulkanDevice.hpp"
#include "Rendering/API/Vulkan/VulkanSwapChain.hpp"
#include "Rendering/API/Vulkan/VulkanCommandPool.hpp"


class VulkanCommandBuffer final : public ICommandBuffer {

public:
	void Create(IDevice* a_device,ISwapChain* a_swapChain,ICommandPool* a_commandPool) override;
	void Destroy() override;

	VulkanCommandBuffer* CastVulkan() override { return this; }

};