#include "Application.hpp"

#include <iostream>

Application::Application()
{
	std::cout << "iNIT\n";

	s_Window.Initialize("Luminous Window", 800, 600);
	//s_Window.InputManager(DebugInput);
}

void Application::Run() const
{
	s_Window.Update();
}