#pragma once

#include "Interface/IWindowPanel.hpp"

class HierarchyWindow : public IWindowPanel
{
public:
    explicit HierarchyWindow(Editor* a_editor, const std::string& a_windowIdentifier) : IWindowPanel(a_editor, a_windowIdentifier) {};

    void Init() override {};
    void Update() override {};
    void Draw() override;
    void Destroy() override {};
};
