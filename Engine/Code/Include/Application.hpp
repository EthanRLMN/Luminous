#pragma once

#include "Exporter.hpp"
#include "Rendering/Window.hpp"

#include "Rendering/LantualRenderHardwareInterface.h"

class LUMINOUS_ENGINE_API Application
{
public:
	Application();
	~Application();

	void Run() const;


private:
	Window s_Window{};

	LantualRender* lantualRender;
	LantualInstance* lantualInstance;
	LantualSurface* lantualSurface;
	LantualDevice* lantualDevice;
	LantualSwapChain* lantualSwapChain;
	LantualRenderPass* lantualRenderPass;
	LantualPipeline* lantualPipeline;
	LantualBuffer* lantualBuffer;
	LantualSynchronisation* lantualSynchronisation;
};
