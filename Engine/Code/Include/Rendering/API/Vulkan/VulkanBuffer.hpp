#pragma once

#include "IBuffer.hpp"
#include <vulkan/vulkan.hpp>


#include "ITexture.hpp"
#include "ICommandPool.hpp"
#include "IDepthResource.hpp"

class VulkanBuffer final : public IBuffer
{
public:
	VulkanBuffer() = default;

	void Create(IDevice* a_device, ITexture* a_texture, ICommandPool* a_commandPool, IDepthResource* a_depthResource) override;
	void Destroy() override;


private:
	void CreateVertexBuffers(IDevice* a_device,ITexture* a_texture,ICommandPool* a_commandPool,IDepthResource* a_depthResource);
	void CreateIndexBuffers(IDevice* a_device, ITexture* a_texture, ICommandPool* a_commandPool,IDepthResource* a_depthResource);
	void CreateUniformBuffers(IDevice* a_device,ITexture* a_texture, IDepthResource* a_depthResource);




};
