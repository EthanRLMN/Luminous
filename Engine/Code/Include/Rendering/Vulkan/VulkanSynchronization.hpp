#pragma once

#include <vector>
#include <vulkan/vulkan.h>

#include "ISynchronization.hpp"

class VulkanSynchronization final : public ISynchronization
{
public:
	void Create(IDevice* a_device) override;
	void Destroy(IDevice* a_device) override;


	VulkanSynchronization* CastVulkan() override { return this; }

	[[nodiscard]] std::vector<VkSemaphore> GetImageAvailableSemaphores() const { return m_imageAvailableSemaphores; }
	[[nodiscard]] std::vector<VkSemaphore> GetRenderFinishedSemaphores() const { return m_renderFinishedSemaphores; }
	[[nodiscard]] std::vector<VkFence>  GetFences() const { return m_fences; }

private:
	std::vector<VkSemaphore> m_imageAvailableSemaphores{ nullptr };
	std::vector<VkSemaphore> m_renderFinishedSemaphores{ nullptr };
	std::vector<VkFence> m_fences{ nullptr };

};
