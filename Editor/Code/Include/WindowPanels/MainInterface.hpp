#pragma once
#include "Interface/IWindowPanel.hpp"

class MainInterface : public IWindowPanel
{
  public:
    explicit MainInterface(Editor* a_editor, const std::string& a_windowIdentifier);

    void Init() override {};
    void Update() override {};
    void Draw() override;
    void Destroy() override {};
};
