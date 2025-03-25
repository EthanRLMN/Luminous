#pragma once

#include "ImguiWindow.hpp"

struct SDL_Window;
using SDL_GLContext = void*;
class Window
{
public:
    Window() = default;
    ~Window() = default;

    void Create();
    void Shutdown();

    void PumpEvents();

    void GetSize(int& w, int& h);

    SDL_Window* GetSDLWindow() { return m_window; }
    SDL_GLContext GetGLContext() { return m_GLContext; }

    void BeginRender();
    void EndRender();

private:
    SDL_Window* m_window;
    SDL_GLContext m_GLContext;
    ImguiWindow m_ImguiWindow;
};
