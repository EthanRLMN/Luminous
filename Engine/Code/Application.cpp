#include "Application.hpp"

#include <iostream>

Application::Application()
{
	std::cout << "Init\n";

	s_Window.Initialize("Luminous Window", 800, 600);
	//s_Window.InputManager(DebugInput);

	lantualInstance = lantualRender->InstantiateContext();
	lantualInstance->Create(&s_Window);

	lantualSurface = lantualRender->InstantiateSurface();
	lantualSurface->Create(lantualInstance, &s_Window);

	lantualDevice = lantualRender->InstantiateDevice();
	lantualDevice->Create(lantualInstance, &s_Window, lantualSurface);

	lantualSwapChain = lantualRender->InstantiateSwapChain();
	lantualSwapChain->Create(&s_Window, lantualDevice, lantualSurface);

	lantualRenderPass = lantualRender->InstantiateRenderPass();
	lantualRenderPass->Create(lantualSwapChain, lantualDevice);

	lantualPipeline = lantualRender->InstantiatePipeline();
	lantualPipeline->Create();


	lantualBuffer = lantualRender->InstantiateBuffer();
	lantualBuffer->Create();

	lantualSynchronisation = lantualRender->InstantiateSynchronisation();
	lantualSynchronisation->Create();
}

Application::~Application() {

	s_Window.Shutdown();

	lantualInstance->Destroy();
	//lantualRender->DeleteContext(lantualInstance);
}

void Application::Run() const
{
	s_Window.Update();
}

