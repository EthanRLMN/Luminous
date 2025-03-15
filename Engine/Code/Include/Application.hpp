#pragma once

#include "Utils/Exporter.hpp"
#include "IBuffer.hpp"
#include "IRender.hpp"
#include "ISynchronisation.hpp"

class VulkanRenderInterface;

class LUMINOUS_ENGINE_API Application
{
public:
	Application();
	~Application();

	void Run() const;

private:
	IRender* m_interface { nullptr };
	IWindow* m_window{ nullptr };
	IInputManager* m_inputManager{ nullptr };

	IRender* m_render { nullptr };
	IInstance* m_instance { nullptr };
	ISurface* m_surface { nullptr };
	IDevice* m_device { nullptr };
	ISwapChain* m_swapChain { nullptr };
	IRenderPass* m_renderPass { nullptr };
	IDescriptions* m_descriptions{ nullptr };
	IPipeline* m_pipeline { nullptr };
	IBuffer* m_buffer { nullptr };
	ISynchronisation* m_synchronisation { nullptr };
};