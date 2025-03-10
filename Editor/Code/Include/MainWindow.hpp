#pragma once

class Window;

class MainWindow
{
public:
    MainWindow() = default;
    ~MainWindow() = default;

    void SetupImGUIContext(Window a_window);
};
