#pragma once

#include "IRender.hpp"
#include "ISynchronization.hpp"
#include "ResourceManager/ResourceManager.hpp"

#include "Physics/physics_JOLT.hpp"



class VulkanRenderInterface;

class Engine
{
public:
	Engine() = default;
	~Engine() = default;

    void Init();
	void Update();
    void UpdatePhysic() const;
	void Destroy() const;

	[[nodiscard]] IWindow* GetWindow() const { return m_window; }
	[[nodiscard]] IInputManager* GetInputManager() const { return m_inputManager; }

	[[nodiscard]] IInstance* GetInstance() const { return m_instance; }
	[[nodiscard]] ISurface* GetSurface() const { return m_surface; }
	[[nodiscard]] IDevice* GetDevice() const { return m_device; }
	[[nodiscard]] ISwapChain* GetSwapChain() const { return m_swapChain; }
	[[nodiscard]] IRenderPass* GetRenderPass() const { return m_renderPass; }
	[[nodiscard]] IRenderPass* GetEditorRenderPass() const { return m_editorRenderPass; }
	[[nodiscard]] IDescriptorSetLayout* GetDescriptionSetLayout() const { return m_descriptorSetLayout; }
	[[nodiscard]] IResourceManager* GetResourceManager() const { return m_resourceManager; }
	[[nodiscard]] IPipeline* GetPipeline() const { return m_pipeline; }
	[[nodiscard]] ICommandPool* GetCommandPool() const { return m_commandPool; }
	[[nodiscard]] ICommandPool* GetEditorCommandPool() const { return m_editorCommandPool; }
	[[nodiscard]] IDepthResource* GetDepthResource() const { return m_depthResource; }
	[[nodiscard]] IFrameBuffer* GetFrameBuffer() const { return m_frameBuffer; }
	[[nodiscard]] ITexture* GetTexture() const { return m_texture; }
	[[nodiscard]] IBuffer* GetBuffer() const { return m_buffer; }
	[[nodiscard]] IDescriptor* GetDescriptor() const { return m_descriptor; }
	[[nodiscard]] ICommandBuffer* GetCommandBuffer() const { return m_commandBuffer; }
	[[nodiscard]] ISynchronization* GetSynchronization() const { return m_synchronization; }
	[[nodiscard]] IRenderer* GetRenderingDraw() const { return m_renderer; }
    [[nodiscard]] bool IsRunning() const { return m_isRunning; }


private:
	IRender* m_interface { nullptr };
	IWindow* m_window { nullptr };
	IInputManager* m_inputManager { nullptr };
	IResourceManager* m_resourceManager{ nullptr };
	IInstance* m_instance { nullptr };
	ISurface* m_surface { nullptr };
	IDevice* m_device { nullptr };
	ISwapChain* m_swapChain { nullptr };
	IRenderPass* m_renderPass { nullptr };
	IRenderPass* m_editorRenderPass { nullptr };
	IDescriptorSetLayout* m_descriptorSetLayout { nullptr };
	IPipeline* m_pipeline { nullptr };
	ICommandPool* m_commandPool{ nullptr };
    IMultiSampling* m_multiSampling{ nullptr };
	ICommandPool* m_editorCommandPool{ nullptr };
	IDepthResource* m_depthResource{ nullptr };
	IFrameBuffer* m_frameBuffer{ nullptr };
	ITexture* m_texture{ nullptr };
	IMesh* m_mesh{ nullptr };
	IBuffer* m_buffer { nullptr };
	IDescriptor* m_descriptor{ nullptr };
	ICommandBuffer* m_commandBuffer{ nullptr };
	ISynchronization* m_synchronization { nullptr };
    IRenderer* m_renderer { nullptr };
	Physics* m_physicsJolt{ nullptr };

    bool m_isRunning { false };
};