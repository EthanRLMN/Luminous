#pragma once

#include "Utils/Exporter.hpp"

#include "IBuffer.hpp"
#include "IRender.hpp"
#include "ISynchronization.hpp"

class VulkanRenderInterface;

class LUMINOUS_ENGINE_API Application
{
public:
	Application();
	~Application();

	void Run() const;

	[[nodiscard]] IWindow* GetWindow() const { return m_window; }
	[[nodiscard]] IInputManager* GetInputManager() const { return m_inputManager; }
	[[nodiscard]] IInstance* GetInstance() const { return m_instance; }
	[[nodiscard]] ISurface* GetSurface() const { return m_surface; }
	[[nodiscard]] IDevice* GetDevice() const { return m_device; }
	[[nodiscard]] ISwapChain* GetSwapChain() const { return m_swapChain; }
	[[nodiscard]] IRenderPass* GetRenderPass() const { return m_renderPass; }
	[[nodiscard]] IDescriptor* GetDescriptor() const { return m_descriptor; }
	[[nodiscard]] IPipeline* GetPipeline() const { return m_pipeline; }
	[[nodiscard]] ICommandPool* GetCommandPool() const { return m_commandPool; }
	[[nodiscard]] IDepthResource* GetDepthResource() const { return m_depthResource; }
	[[nodiscard]] IFrameBuffer* GetFrameBuffer() const { return m_frameBuffer; }
	[[nodiscard]] ITexture* GetTexture() const { return m_texture; }
	[[nodiscard]] IBuffer* GetBuffer() const { return m_buffer; }
	[[nodiscard]] ISynchronization* GetSynchronization() const { return m_synchronization; }

private:
	IRender* m_interface { nullptr };
	IWindow* m_window { nullptr };
	IInputManager* m_inputManager { nullptr };

	IInstance* m_instance { nullptr };
	ISurface* m_surface { nullptr };
	IDevice* m_device { nullptr };
	ISwapChain* m_swapChain { nullptr };
	IRenderPass* m_renderPass { nullptr };
	IDescriptor* m_descriptor { nullptr };
	IPipeline* m_pipeline { nullptr };
	ICommandPool* m_commandPool{ nullptr };
	IDepthResource* m_depthResource{ nullptr };
	IFrameBuffer* m_frameBuffer{ nullptr };
	ITexture* m_texture{ nullptr };

	IBuffer* m_buffer { nullptr };
	ISynchronization* m_synchronization { nullptr };
};