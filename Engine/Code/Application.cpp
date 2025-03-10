#include "Application.hpp"

#include <iostream>

Application::Application()
{
	std::cout << "Init\n";

	m_window.Initialize("Luminous Window", 800, 600);
	//s_Window.InputManager(DebugInput);

	m_instance = m_render->InstantiateContext();
	m_instance->Create(&m_window);

	m_surface = m_render->InstantiateSurface();
	m_surface->Create(m_instance, &m_window);

	m_device = m_render->InstantiateDevice();
	m_device->Create(m_instance, &m_window, m_surface);

	m_swapChain = m_render->InstantiateSwapChain();
	m_swapChain->Create(&m_window, m_device, m_surface);

	m_renderPass = m_render->InstantiateRenderPass();
	m_renderPass->Create(m_swapChain, m_device);

	m_pipeline = m_render->InstantiatePipeline();
	m_pipeline->Create();


	m_buffer = m_render->InstantiateBuffer();
	m_buffer->Create();

	m_synchronisation = m_render->InstantiateSynchronisation();
	m_synchronisation->Create();
}

Application::~Application() {

	m_window.Shutdown();

	m_instance->Destroy();
	//lantualRender->DeleteContext(lantualInstance);
}

void Application::Run() const
{
	m_window.Update();
}

