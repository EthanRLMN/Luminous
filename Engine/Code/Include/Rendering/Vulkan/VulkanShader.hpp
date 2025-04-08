#pragma once

#include <string>
#include <vulkan/vulkan.h>

#include "IShader.hpp"
#include "Struct/VulkanUtilities.hpp"
#include "Rendering/Vulkan/VulkanShaderModule.hpp"

class VulkanShader final : public IShader
{
public:
    bool Create(IResourceManager* a_manager, IResourceParams a_params) override;
    void Destroy(IDevice* a_device) override ;


    VulkanShader* CastVulkan() override { return this; }

    inline VulkanShaderModule GetVertexShaderModule() { return m_vertexShaderModule; }
    inline VulkanShaderModule GetFragmentShaderModule() { return m_fragmentShaderModule; }
    inline VulkanShaderModule GetTesselationShaderModule() { return m_tesselationShaderModule; }
    inline VulkanShaderModule GetGeometryShaderModule() { return m_geometryShaderModule; }

private:
    VulkanShaderModule m_vertexShaderModule;
    VulkanShaderModule m_fragmentShaderModule;
    VulkanShaderModule m_tesselationShaderModule;
    VulkanShaderModule m_geometryShaderModule;
};
