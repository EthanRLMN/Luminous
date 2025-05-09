#pragma once

#include "Interface/IWindowPanel.hpp"

class InspectorPanel : public IWindowPanel
{
public:
    explicit InspectorPanel(Editor* a_editor, const std::string& a_windowIdentifier) : IWindowPanel(a_editor, a_windowIdentifier) {};

    void Init() override {};
    void Update() override {};
    void Render() override;
    void Destroy() override {};
};
