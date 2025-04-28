#include "Rendering/Vulkan/VulkanRenderPassManager.hpp"

#include "Rendering/Vulkan/VulkanRenderPass.hpp"

void VulkanRenderPassManager::Create(ISwapChain* a_swapChain, IDevice* a_device, const bool& a_isEditor)
{
    m_renderPass = new VulkanRenderPass();

    if (a_isEditor)
        m_renderPass->CastVulkan()->CreateEditorPass(a_swapChain, a_device);
    else
        m_renderPass->CastVulkan()->Create(a_swapChain, a_device);

    p_renderPasses.push_back(m_renderPass);
}

void VulkanRenderPassManager::Destroy(IDevice* a_device)
{
    for (IRenderPass* l_renderPass : p_renderPasses)
    {
        l_renderPass->Destroy(a_device);
        delete l_renderPass;
    }
    p_renderPasses.clear();
    m_renderPass = nullptr;
}
