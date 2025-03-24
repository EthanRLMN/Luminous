#pragma once

typedef union SDL_Event SDL_Event;
class MainWindow
{
public:
    MainWindow() = default;
    ~MainWindow() = default;

    void Create();
    void Shutdown();

    void HandleSLDEvent(SDL_Event& e);

    void BeginRender();
    void EndRender();
};
