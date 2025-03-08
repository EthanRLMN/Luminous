#pragma once

#include "Exporter.hpp"
#include "Rendering/Window.hpp"

class LUMINOUS_ENGINE_API Application
{
public:
	Application();
	~Application() = default;

	void Run() const;

	Window s_Window{};
};
