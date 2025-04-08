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



private:
    VulkanShaderModule m_vertexShaderModule;
    VulkanShaderModule m_fragmentShaderModule;
    VulkanShaderModule m_tesselationShaderModule;
    VulkanShaderModule m_geometryShaderModule;
};
