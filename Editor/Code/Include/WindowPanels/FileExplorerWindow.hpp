#pragma once

#include "Interface/IWindowPanel.hpp"

#include <filesystem>

class FileExplorerWindow : public IWindowPanel
{
public:
    explicit FileExplorerWindow(Editor* a_editor, const std::string& a_windowIdentifier) : IWindowPanel(a_editor, a_windowIdentifier) {}

    void ContentBrowserPanel();

    void Init() override {};
    void Update() override {};
    void Draw() override;
    void Destroy() override {};

private:
    std::filesystem::path m_currentDirectory;
};
