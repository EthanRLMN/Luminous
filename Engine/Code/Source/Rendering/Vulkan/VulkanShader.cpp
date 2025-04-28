#include "Rendering/Vulkan/VulkanShader.hpp"
#include "ResourceManager/ResourceManager.hpp"

bool VulkanShader::Create(IResourceManager* a_manager, IResourceParams a_params)
{

    bool isVertexCreated = m_vertexShaderModule.Create(a_params.m_device, a_params.m_vertexShaderPath);
    bool isFragmentCreated = m_fragmentShaderModule.Create(a_params.m_device, a_params.m_fragmentShaderPath);

    return isVertexCreated && isFragmentCreated;
}

void VulkanShader::Destroy(IDevice* a_device)
{

    m_vertexShaderModule.Destroy(a_device);
    m_fragmentShaderModule.Destroy(a_device);
    m_tesselationShaderModule.Destroy(a_device);
    m_geometryShaderModule.Destroy(a_device);
}
