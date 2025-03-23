#pragma once

#include <vk_mem_alloc.h>

class IDevice;
class IInstance;

class VulkanMemoryAllocator
{
public:
    explicit VulkanMemoryAllocator() = default;
    ~VulkanMemoryAllocator() = default;

    void Init(IInstance* a_instance, IDevice* a_device);
    [[nodiscard]] VmaAllocator GetMemoryAllocator() const { return m_memAllocator; };

private:
    VmaAllocator m_memAllocator;
};
