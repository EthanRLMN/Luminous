#pragma once

class IDevice;
class ISwapChain;
class IDepthResource;
class ICommandPool;
class IDescriptorSetLayout;

struct ResourceContext
{
    IDevice* m_device = nullptr;
    ISwapChain* m_swapChain = nullptr;
    IDepthResource* m_depth = nullptr;
    ICommandPool* m_commandPool = nullptr;
    IDescriptorSetLayout* m_descriptorSetLayout = nullptr;

    inline bool IsValid() const { return m_device && m_swapChain && m_depth && m_commandPool && m_descriptorSetLayout; }
};