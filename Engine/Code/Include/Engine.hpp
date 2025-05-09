#pragma once

#include "IRender.hpp"
#include "ISynchronization.hpp"

#include "Game/Scene.hpp"
#include "Game/Systems/Entity/Entity.hpp"
#include "Game/Systems/Entity/EntityManager.hpp"
#include "Game/Systems/Physics/PhysicsSystem.hpp"


class VulkanRenderInterface;

class Engine
{
public:
	Engine() = default;
	~Engine() = default;

    void Init();
	void Update();
	void Destroy();

	void Window();
    void Input();
	void PreRender();
    void InitPhysics();


	void DestroyWindow();
    void DestroyInput() const;

	[[nodiscard]] IWindow* GetWindow() const { return m_window; }
	[[nodiscard]] IInputManager* GetInputManager() const { return m_inputManager; }
	[[nodiscard]] IInstance* GetInstance() const { return m_instance; }
	[[nodiscard]] ISurface* GetSurface() const { return m_surface; }
	[[nodiscard]] IDevice* GetDevice() const { return m_device; }
	[[nodiscard]] ISwapChain* GetSwapChain() const { return m_swapChain; }
	[[nodiscard]] IRenderPassManager* GetRenderPassManager() const { return m_renderPassManager; }
	[[nodiscard]] IDescriptorSetLayout* GetDescriptionSetLayout() const { return m_descriptorSetLayout; }
	[[nodiscard]] IPipeline* GetPipeline() const { return m_pipeline; }
	[[nodiscard]] ICommandPool* GetCommandPool() const { return m_commandPool; }
	[[nodiscard]] ICommandPool* GetEditorCommandPool() const { return m_editorCommandPool; }
	[[nodiscard]] IDepthResource* GetDepthResource() const { return m_depthResource; }
	[[nodiscard]] IFrameBufferManager* GetFrameBufferManager() const { return m_frameBufferManager; }
	[[nodiscard]] IBuffer* GetBuffer() const { return m_buffer; }
	[[nodiscard]] IDescriptor* GetDescriptor() const { return m_descriptor; }
	[[nodiscard]] ICommandBuffer* GetCommandBuffer() const { return m_commandBuffer; }
	[[nodiscard]] ISynchronization* GetSynchronization() const { return m_synchronization; }
	[[nodiscard]] IRenderer* GetRenderer() const { return m_renderer; }
    [[nodiscard]] Scene* GetScene() const { return m_scene; }
    [[nodiscard]] EntityManager* GetEntityManager() { return &m_entityManager; }

    [[nodiscard]] bool IsRunning() const { return m_isRunning; }


private:
	IRender* m_interface { nullptr };
	IWindow* m_window { nullptr };
	IInputManager* m_inputManager { nullptr };
	IInstance* m_instance { nullptr };
	ISurface* m_surface { nullptr };
	IDevice* m_device { nullptr };
	ISwapChain* m_swapChain { nullptr };
	IRenderPassManager* m_renderPassManager { nullptr };
	IDescriptorSetLayout* m_descriptorSetLayout { nullptr };
	IPipeline* m_pipeline { nullptr };
	ICommandPool* m_commandPool{ nullptr };
    IMultiSampling* m_multiSampling{ nullptr };
	ICommandPool* m_editorCommandPool{ nullptr };
	IDepthResource* m_depthResource{ nullptr };
	IFrameBufferManager* m_frameBufferManager{ nullptr };
	IBuffer* m_buffer { nullptr };
	IDescriptor* m_descriptor{ nullptr };
	ICommandBuffer* m_commandBuffer{ nullptr };
	ISynchronization* m_synchronization { nullptr };
    IRenderer* m_renderer { nullptr };
	Scene* m_scene{ nullptr };
	PhysicsSystem* m_physicsSystem{ nullptr };

    bool m_isRunning { false };

	EntityManager m_entityManager;
};