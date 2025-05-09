#pragma once

#include "Interface/IWindowPanel.hpp"

class HierarchyPanel : public IWindowPanel
{
public:
    explicit HierarchyPanel(Editor* a_editor, const std::string& a_windowIdentifier) : IWindowPanel(a_editor, a_windowIdentifier) {};

    void Init() override {};
    void Update() override {};
    void Render() override;
    void Destroy() override {};
};
