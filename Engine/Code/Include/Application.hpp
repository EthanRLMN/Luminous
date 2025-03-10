#pragma once

#include "Exporter.hpp"
#include "Rendering/IBuffer.hpp"
#include "Rendering/IRender.hpp"
#include "Rendering/ISynchronisation.hpp"
#include "Rendering/Window.hpp"

class LUMINOUS_ENGINE_API Application
{
public:
	Application();
	~Application();

	void Run() const;

private:
	Window m_window{};

	IRender* m_render { nullptr };
	IInstance* m_instance { nullptr };
	ISurface* m_surface { nullptr };
	IDevice* m_device { nullptr };
	ISwapChain* m_swapChain { nullptr };
	IRenderPass* m_renderPass { nullptr };
	IPipeline* m_pipeline { nullptr };
	IBuffer* m_buffer { nullptr };
	ISynchronisation* m_synchronisation { nullptr };
};
