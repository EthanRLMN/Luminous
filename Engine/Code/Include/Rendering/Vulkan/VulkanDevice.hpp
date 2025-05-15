#pragma once

#include <set>
#include <vulkan/vulkan.h>

#include "IDevice.hpp"

#include "Struct/VulkanUtilities.hpp"
#include "Utils/QueueFamilyIndiceUtils.hpp"

class VulkanDevice final : public IDevice
{
public:
    ~VulkanDevice() override = default;
    void Create(IInstance* a_instance, ISurface* a_surface) override;
    void Destroy() override;
    VulkanDevice* CastVulkan() override { return this; }

    void CreateLogicalDevice(const VkSurfaceKHR& a_surface);
    void GetPhysicalDevice(const VkInstance& a_instance, const VkSurfaceKHR& a_surface);

    static bool CheckDeviceSuitable(const VkPhysicalDevice& a_device, const VkSurfaceKHR& a_surface);
    static bool CheckDeviceExtensionSupport(const VkPhysicalDevice& a_device);

    [[nodiscard]] VkSampleCountFlagBits GetMSAASamples() const { return m_msaaSamples; }
    static SwapChainDetails GetSwapChainDetails(const VkPhysicalDevice& a_device, const VkSurfaceKHR& a_surface);
    static QueueFamilyIndices GetQueueFamilies(const VkPhysicalDevice& a_device, const VkSurfaceKHR& a_surface);

    [[nodiscard]] VkDevice GetDevice() const { return m_device; }
    [[nodiscard]] VkPhysicalDevice GetPhysicalDevice() const { return m_physicalDevice; }
    [[nodiscard]] VkQueue GetGraphicsQueue() const { return m_graphicsQueue; }
    [[nodiscard]] VkQueue GetPresentationQueue() const { return m_presentationQueue; }

    void SetMSAASamples(const VkSampleCountFlagBits& a_sampleCount) { m_msaaSamples = a_sampleCount; }

    void WaitIdle() const;

private :
    void ProcessLogicalDeviceInfo(const QueueFamilyIndices& a_queueFamilyIndices);
    static void AssignQueueFamilyIndices(const std::set<int>& a_queueFamilyIndices, std::vector<VkDeviceQueueCreateInfo>& a_queueCreateInfos);

    VkDevice m_device{ nullptr };
    VkPhysicalDevice m_physicalDevice{ nullptr };
    VkQueue m_graphicsQueue{ nullptr };
    VkQueue m_presentationQueue{ nullptr };

    VkSampleCountFlagBits m_msaaSamples{ VK_SAMPLE_COUNT_1_BIT };
};