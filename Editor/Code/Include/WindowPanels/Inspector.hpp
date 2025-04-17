#pragma once

#include "Interface/IWindowPanel.hpp"

class Inspector : public IWindowPanel
{
public:
    explicit Inspector(Editor* a_editor, const std::string& a_windowIdentifier) : IWindowPanel(a_editor, a_windowIdentifier) {};

    void Init() override {};
    void Update() override {};
    void Draw() override;
    void Destroy() override {};
};
