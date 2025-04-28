#include "Rendering/Vulkan/VulkanShader.hpp"
#include "ResourceManager/ResourceManager.hpp"

bool VulkanShader::Create(IResourceManager* a_manager, const IResourceParams& a_params)
{
    const bool l_isVertexCreated = m_vertexShaderModule.Create(a_params.m_device, a_params.m_vertexShaderPath);
    const bool l_isFragmentCreated = m_fragmentShaderModule.Create(a_params.m_device, a_params.m_fragmentShaderPath);

    return l_isVertexCreated && l_isFragmentCreated;
}

void VulkanShader::Destroy(IDevice* a_device)
{
    m_vertexShaderModule.Destroy(a_device);
    m_fragmentShaderModule.Destroy(a_device);
    m_tesselationShaderModule.Destroy(a_device);
    m_geometryShaderModule.Destroy(a_device);
}
