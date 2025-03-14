#include "Wrapper/EWindow.hpp"
/*
EWindow::EWindow(const int a_width, const int a_height, const char* a_title)
{
	m_window = glfwCreateWindow(a_width, a_height, a_title, nullptr, nullptr);
}


EWindow::~EWindow()
{
	if (m_window != nullptr)
		glfwDestroyWindow(m_window);
}

void EWindow::Update()
{
	while (!WindowShouldClose())
	{
		//glfwPollEvents();

	}
}

void EWindow::Close()
{
	delete(this);
}

int EWindow::WindowShouldClose()
{
	return glfwWindowShouldClose(m_window);
}

void EWindow::SetWindowShouldClose(int a_value)
{
	glfwSetWindowShouldClose(m_window, a_value);
}

Vector2 EWindow::GetSize()
{
	int t_x, t_y;
	glfwGetWindowSize(m_window, &t_x, &t_y);
	return Vector2((float)t_x, (float)t_y);
}

void EWindow::SetSize(const Vector2 a_size)
{
	glfwSetWindowSize(m_window, (int)a_size.x, (int)a_size.y);
}

float EWindow::GetOpacity()
{
	return glfwGetWindowOpacity(m_window);
}

void EWindow::SetOpacity(const float a_alpha)
{
	glfwSetWindowOpacity(m_window, a_alpha);
}

VulkanWindow* EWindow::CastToVulkan()
{
	return nullptr;
}*/
