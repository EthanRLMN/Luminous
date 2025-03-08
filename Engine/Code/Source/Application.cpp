#include "Application.h"

Application::Application()
{
	std::cout << "iNIT\n";

	s_Window.Initialize("Luminous Window", 800, 600);
	s_Window.InputManager(DebugInput);

}

Application::~Application()
{
}

void Application::Run()
{
	s_Window.Update();
}


void Application::DebugInput(GLFWwindow* window, int _key, int _scancode, int _action, int _mods) {

	if (_key == GLFW_KEY_SPACE && _action == GLFW_PRESS) {
		std::cout << "Espace appuyer" << std::endl;
	}
}