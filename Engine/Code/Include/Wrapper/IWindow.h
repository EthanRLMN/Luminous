
#include "../../../Libs/glfw/include/GLFW/glfw3.h"

class Vector2 { public:Vector2() = default;Vector2(float ax, float ay) { x = ax; y = ay; }; float x = 0, y = 0; };

class IWindow
{
public:
	IWindow() = default;
	IWindow(const int a_width, const int a_height, const char* a_title);
	~IWindow();
	Vector2 GetSize();
	void SetSize(const Vector2 a_size);
	float GetOpacity();
	void SetOpacity(const float a_alpha);

private:
	GLFWwindow* m_window;
};