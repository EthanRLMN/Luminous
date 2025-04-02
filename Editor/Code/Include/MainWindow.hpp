#include "imgui.h"

class MainWindow
{
  public:
    MainWindow();
    ~MainWindow();

    void Draw();

    bool m_isOpen;
};