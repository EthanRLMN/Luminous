#pragma once

class MainWindow
{
  public:
    MainWindow() = default;
    ~MainWindow() = default;

    void Draw();

private:
    bool m_isOpen;
};