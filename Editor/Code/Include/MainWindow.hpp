#include "imgui.h"

class MainWindow
{
  public:
    MainWindow();
    ~MainWindow();

    void Draw();

private:
    bool m_isOpen;
};