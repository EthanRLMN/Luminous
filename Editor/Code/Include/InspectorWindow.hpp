#include "imgui.h"
#include "MainWindow.hpp"

class InspectorWindow
{
public:
    InspectorWindow() = default;
    ~InspectorWindow() = default;

    void Draw();
private:
    bool m_isOpen;
};