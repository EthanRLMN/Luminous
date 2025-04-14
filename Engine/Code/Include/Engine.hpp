#pragma once

#include <functional>

#include "IRender.hpp"
#include "ISynchronization.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "jolt/Jolt/Jolt.h"
#include "jolt/Jolt/RegisterTypes.h"
#include "jolt/Jolt/Core/Factory.h"
#include "jolt/Jolt/Physics/Collision/Shape/BoxShape.h"
#include "jolt/Jolt/Physics/Collision/Shape/SphereShape.h"
#include "jolt/Jolt/Physics/Body/BodyCreationSettings.h"


class VulkanRenderInterface;

class Engine
{
public:
	Engine() = default;
	~Engine() = default;

    void Init();
    void InitPhysic();
	void Update();
    void UpdatePhysic();
	void Destroy() const;

	[[nodiscard]] IWindow* GetWindow() const { return m_window; }
	[[nodiscard]] IInputManager* GetInputManager() const { return m_inputManager; }

	[[nodiscard]] IInstance* GetInstance() const { return m_instance; }
	[[nodiscard]] ISurface* GetSurface() const { return m_surface; }
	[[nodiscard]] IDevice* GetDevice() const { return m_device; }
	[[nodiscard]] ISwapChain* GetSwapChain() const { return m_swapChain; }
	[[nodiscard]] IRenderPass* GetRenderPass() const { return m_renderPass; }
	[[nodiscard]] IRenderPass* GetUIRenderPass() const { return m_uiRenderPass; }
	[[nodiscard]] IDescriptorSetLayout* GetDescriptionSetLayout() const { return m_descriptorSetLayout; }
	[[nodiscard]] IPipeline* GetPipeline() const { return m_pipeline; }
	[[nodiscard]] ICommandPool* GetCommandPool() const { return m_commandPool; }
	[[nodiscard]] IDepthResource* GetDepthResource() const { return m_depthResource; }
	[[nodiscard]] IFrameBuffer* GetFrameBuffer() const { return m_frameBuffer; }
	[[nodiscard]] ITexture* GetTexture() const { return m_texture; }
	[[nodiscard]] IBuffer* GetBuffer() const { return m_buffer; }
	[[nodiscard]] IDescriptor* GetDescriptor() const { return m_descriptor; }
	[[nodiscard]] ICommandBuffer* GetCommandBuffer() const { return m_commandBuffer; }
	[[nodiscard]] ISynchronization* GetSynchronization() const { return m_synchronization; }
	[[nodiscard]] IRenderingDraw* GetRenderingDraw() const { return m_renderingDraw; }

    bool IsRunning() const { return m_isRunning; }


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
	IRenderPass* m_uiRenderPass { nullptr };
	IDescriptorSetLayout* m_descriptorSetLayout { nullptr };
	IPipeline* m_pipeline { nullptr };
	ICommandPool* m_commandPool{ nullptr };
	IDepthResource* m_depthResource{ nullptr };
	IFrameBuffer* m_frameBuffer{ nullptr };
	ITexture* m_texture{ nullptr };
	IMesh* m_mesh{ nullptr };
	IBuffer* m_buffer { nullptr };
	IDescriptor* m_descriptor{ nullptr };
	ICommandBuffer* m_commandBuffer{ nullptr };
	ICommandBuffer* m_editorCommandBuffer{ nullptr };
	ISynchronization* m_synchronization { nullptr };
    IRenderingDraw* m_renderingDraw { nullptr };

	JPH::PhysicsSystem* m_physicsSystem = nullptr; 
    JPH::BodyInterface* m_bodyInterface = nullptr; 
    JPH::ShapeManager* m_shapeManager = nullptr; 

    bool m_isRunning { false };
};