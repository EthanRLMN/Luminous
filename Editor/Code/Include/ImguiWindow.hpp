#pragma once

typedef union SDL_Event SDL_Event;
using SDL_GLContext = void*;

class ImguiWindow
{
public:
	ImguiWindow() {}
	~ImguiWindow() {}

	void Create();
	void Shutdown();

	void HandleSLDEvent(SDL_Event& e);

	void BeginRender();
	void EndRender();
}