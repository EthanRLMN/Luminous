#include "imgui.h"
#include "MainWindow.hpp"

class FoldersWindow
{
public:
    FoldersWindow() = default;
    ~FoldersWindow() = default;

    void Draw();

private:
    bool m_isOpen;
};