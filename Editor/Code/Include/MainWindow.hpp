#pragma once

class Window;

class MainWindow
{
public:
    MainWindow() = default;
    ~MainWindow() = default;

    void Open()
    {
        m_isOpen = true;
    }

    void Close()
    {
        m_isOpen = false;
    }
    void Draw();

    //void SetupImGUIContext(Window a_window);

private:
    bool m_isOpen = true;
};
