#pragma once

#include "IShader.hpp"

#include "Rendering/Vulkan/VulkanShaderModule.hpp"

class VulkanShader final : public IShader
{
public:
    bool Create(const IResourceParams& a_params) override;
    void Destroy(IDevice* a_device) override;

    VulkanShader* CastVulkan() override { return this; }

    VulkanShaderModule* GetVertexShaderModule() { return &m_vertexShaderModule; }
    VulkanShaderModule* GetFragmentShaderModule() { return &m_fragmentShaderModule; }
    VulkanShaderModule* GetTesselationShaderModule() { return &m_tesselationShaderModule; }
    VulkanShaderModule* GetGeometryShaderModule() { return &m_geometryShaderModule; }

private:
    VulkanShaderModule m_vertexShaderModule{};
    VulkanShaderModule m_fragmentShaderModule{};
    VulkanShaderModule m_tesselationShaderModule{};
    VulkanShaderModule m_geometryShaderModule{};
};
