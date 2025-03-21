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

	m_descriptionSetLayout = m_interface->InstantiateDescriptionSetLayout();
	m_descriptionSetLayout->Create(m_device);

	m_pipeline = m_interface->InstantiatePipeline();
	m_pipeline->Create(m_device, m_renderPass, m_descriptionSetLayout);

	m_commandPool = m_interface->InstantiateCommandPool();
	m_commandPool->Create(m_device, m_surface);

	m_depthResource = m_interface->InstantiateDepthResource();
	m_depthResource->Create(m_device, m_swapChain, m_renderPass);

	m_frameBuffer = m_interface->InstantiateFrameBuffer();
	m_frameBuffer->Create(m_device, m_swapChain, m_renderPass, m_depthResource);

	m_texture = m_interface->InstantiateTexture();
	m_texture->Create(m_device, m_swapChain, m_depthResource, m_commandPool);

	m_model = m_interface->InstantiateModel();
	m_model->Create();

	m_buffer = m_interface->InstantiateBuffer();
	m_buffer->Create(m_device,m_texture,m_commandPool,m_depthResource);



	/*

	m_buffer = m_interface->InstantiateBuffer();
	m_buffer->Create();

	m_synchronisation = m_interface->InstantiateSynchronisation();
	m_synchronisation->Create();*/
}

Application::~Application()
{
	m_pipeline->Destroy();
	m_interface->DeletePipeline(m_pipeline);

	m_descriptionSetLayout->Destroy();
	m_interface->DeleteDescriptionSetLayout(m_descriptionSetLayout);

	m_renderPass->Destroy(m_device);
	m_interface->DeleteRenderPass(m_renderPass);

	m_swapChain->Destroy(m_device);
	m_interface->DeleteSwapChain(m_swapChain);

	m_device->Destroy();
	m_interface->DeleteDevice(m_device);

	m_surface->Destroy(m_instance);
	m_interface->DeleteSurface(m_surface);

	m_instance->Destroy();

	m_inputManager->Destroy(m_window);
	m_interface->DeleteInputManager(m_inputManager);

	m_window->Destroy();

	delete(m_window);
}

void Application::Run() const
{
	while (!m_window->ShouldClose())
	{
		m_window->PollEvents();
		/*if (m_inputManager->IsKeyPressed(m_window, Key::KEY_A))
			DEBUG_LOG_VERBOSE("Key {} has been pressed!\n", Key::KEY_A);

		if (m_inputManager->IsMouseButtonDown(m_window, MouseButton::MOUSE_BUTTON_LEFT))
			DEBUG_LOG_VERBOSE("x={}, y={}\n", m_inputManager->GetMouseScroll().x, m_inputManager->GetMouseScroll().y);*/

		m_inputManager->Update(m_window);
	}
	m_window->Destroy();
}

