#include "imgui.h"
#include "MainWindow.hpp"

class InspectorWindow
{
public:
    InspectorWindow();
    ~InspectorWindow();

    void Draw();
private:
    bool m_isOpen;
};