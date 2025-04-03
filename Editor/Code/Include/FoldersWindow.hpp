#include "imgui.h"
#include "MainWindow.hpp"

class FoldersWindow
{
public:
    FoldersWindow();
    ~FoldersWindow();

    void Draw();

private:
    bool m_isOpen;
};