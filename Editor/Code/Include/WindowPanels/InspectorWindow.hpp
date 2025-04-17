#pragma once

#include "Interface/IWindowPanel.hpp"

class InspectorWindow : public IWindowPanel
{
public:
    explicit InspectorWindow(Editor* a_editor, const std::string& a_windowIdentifier) : IWindowPanel(a_editor, a_windowIdentifier) {};

    void Init() override {};
    void Update() override {};
    void Draw() override;
    void Destroy() override {};
};
