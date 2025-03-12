#include "Wrapper/IWindow.h"

IWindow::IWindow(const int a_width, const int a_height, const char* a_title)
{
	m_window = glfwCreateWindow(a_width, a_height, a_title, nullptr, nullptr);
}


IWindow::~IWindow()
{	
	if (m_window != nullptr)
		glfwDestroyWindow(m_window);
}

Vector2 IWindow::GetSize()
{
	int t_x, t_y;
	glfwGetWindowSize(m_window, &t_x, &t_y);
	return Vector2(t_x,t_y);
}

void IWindow::SetSize(const Vector2 a_size)
{
	glfwSetWindowSize(m_window, a_size.x, a_size.y);
}

float IWindow::GetOpacity()
{
	return glfwGetWindowOpacity(m_window);
}

void IWindow::SetOpacity(const float a_alpha)
{
	glfwSetWindowOpacity(m_window, a_alpha);
}
