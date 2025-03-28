#pragma once

typedef union SDL_Event SDL_Event;

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
};