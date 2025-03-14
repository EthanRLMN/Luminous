#include "Application.hpp"

#include "Rendering/API/Vulkan/VulkanRenderInterface.hpp"

Application::Application()
{
	Debug::Logger& l_logger = Debug::Logger::GetInstance();
	l_logger.Init("app", 1_MiB, 5, true);

	m_interface = new VulkanRenderInterface();

	m_window = m_interface->InstantiateWindow();
	m_window->Initialize("Luminous Window", 800, 600);

	m_inputManager = m_interface->InstantiateInputManager();
	m_inputManager->Initialize(m_window);

	m_instance = m_interface->InstantiateContext();
	m_instance->Create(m_window);

	m_surface = m_interface->InstantiateSurface();
	m_surface->Create(m_instance, m_window);

	m_device = m_interface->InstantiateDevice();
	m_device->Create(m_instance, m_window, m_surface);

	m_swapChain = m_interface->InstantiateSwapChain();
	m_swapChain->Create(m_window, m_device, m_surface);

	m_renderPass = m_interface->InstantiateRenderPass();
	m_renderPass->Create(m_swapChain, m_device);

	m_pipeline = m_interface->InstantiatePipeline();
	m_pipeline->Create();

	m_buffer = m_interface->InstantiateBuffer();
	m_buffer->Create();

	m_synchronisation = m_interface->InstantiateSynchronisation();
	m_synchronisation->Create();

	std::cout << m_window->GetSize().x << '\n';
	std::cout << m_window->GetSize().y << '\n';
	m_window->SetOpacity(0.5f);
}

Application::~Application()
{
	delete(m_window);
	//m_window->Destroy();
	m_instance->Destroy();
}

void Application::Run() const
{
	while (!m_window->ShouldClose())
	{
		m_window->PollEvents();
		if (m_inputManager->IsKeyDown(m_window, GLFW_KEY_A))
			std::cout << "MEJK";

		if (m_inputManager->IsMouseButtonDown(m_window, GLFW_MOUSE_BUTTON_2))
			std::cout << m_inputManager->GetMouseScroll().x << ", " << m_inputManager->GetMouseScroll().y << '\n';
	}
	m_window->Destroy();
}

