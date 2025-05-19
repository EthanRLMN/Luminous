#pragma once

#include "Interface/IWindowPanel.hpp"


class ConsolePanel : public IWindowPanel
{
public:
    explicit ConsolePanel(Editor* a_editor, const std::string& a_windowIdentifier) : IWindowPanel(a_editor, a_windowIdentifier) {};

    void Init() override {};
    void Update() override {};
    void Render() override;
    void Destroy() override {};


private:
    static ImVec4 GetColorForLogLevel(Debug::LogLevel a_level);

    std::vector<std::string> m_items {};
    bool m_autoScroll { true };
};