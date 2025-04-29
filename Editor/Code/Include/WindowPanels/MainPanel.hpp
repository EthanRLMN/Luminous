#pragma once

#include "Interface/IWindowPanel.hpp"


class MainPanel : public IWindowPanel
{
  public:
    explicit MainPanel(Editor* a_editor, const std::string& a_windowIdentifier) : IWindowPanel(a_editor, a_windowIdentifier) {};

    void Init() override {};
    void Update() override {};
    void Render() override;
    void Destroy() override {};

private:
    void FileContextMenu();
    void EditContextMenu();
    void WindowContextMenu();
    void HelpContextMenu();
};
