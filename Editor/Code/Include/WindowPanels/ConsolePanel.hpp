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
    void AddLog(const std::string& a_log);

    std::vector<std::string> m_items;
    std::string m_inputBuffer;
};
