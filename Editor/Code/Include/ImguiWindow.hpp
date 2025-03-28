#pragma once
#include <vulkan/vulkan.h>

class ImguiWindow
{
public:
	ImguiWindow() {}
	~ImguiWindow() {}

	void Create();
	void Shutdown();

	void BeginRender();
	void EndRender();

    bool WantCaptureMouse();
    bool WantCaptureKeyboard();
};