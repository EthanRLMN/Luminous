#pragma once

#include "Exporter.hpp"
#include "Rendering/MainWindow.hpp"

class LUMINOUS_ENGINE_API Application
{
public:
	Application();
	~Application() = default;

	void Run() const;

	MainWindow s_Window{};
};
