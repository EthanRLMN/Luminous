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
    bool RunCommand(const std::string& a_cmd);
    void HelpContextMenu();
    std::string m_scenePath = "Engine/Assets/Default/Save/Scene1.json";
};
