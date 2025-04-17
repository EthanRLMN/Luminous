#pragma once

#include <filesystem>

#include "Interface/IWindowPanel.hpp"


class FileExplorerWindow : public IWindowPanel
{
public:
    explicit FileExplorerWindow(Editor* a_editor, const std::string& a_windowIdentifier);

    void Init() override {};
    void Update() override {};
    void Draw() override;
    void Destroy() override {};

private:
    std::filesystem::path m_currentDirectory{};
};
