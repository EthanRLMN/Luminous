#pragma once 
#include <array>

#include "Logger.hpp"
#include "Struct/VulkanUtilities.hpp"

#include "Utils/FileReaderUtils.hpp"

#include "Rendering/Vulkan/VulkanPipeline.hpp"
#include "Rendering/Vulkan/VulkanDescriptorSetLayout.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Rendering/Vulkan/VulkanRenderPass.hpp"
#include "Rendering/Vulkan/VulkanShader.hpp"
#include "ResourceManager/Resource.hpp"
#include "ResourceManager/ResourceManager.hpp"


class Skybox
{
public:

    void GetSkyboxPipeline() {return m_skyboxPipeline}

private:
    VkPipeline m_skyboxPipeline{ nullptr };
};
