
#include "IMultiSampling.hpp"
#include "vulkan/vulkan.h"
#include "Struct/VulkanUtilities.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"

class VulkanMultiSampling : public IMultiSampling
{
public:
    void Create(IDevice* a_device) override;
    void Destroy(IDevice* a_device) override;

    VkSampleCountFlagBits GetMaxUsableSampleCount(IDevice* a_device);
};
