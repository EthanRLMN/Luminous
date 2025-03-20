#pragma once

class Window;

class MainWindow
{
public:
    MainWindow() = default;
    ~MainWindow() = default;

    void Open()
    {
        isOpen = true;
    }

    void Close()
    {
        isOpen = false;
    }
    void Draw();

    //void SetupImGUIContext(Window a_window);

private:
    bool isOpen = true;
};
