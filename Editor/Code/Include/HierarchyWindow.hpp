#include "MainWindow.hpp"
#include "imgui.h"

class HierarchyWindow
{
public:
    HierarchyWindow() = default;
    ~HierarchyWindow() = default;

    void Draw();
private:
    bool m_isOpen;
};
