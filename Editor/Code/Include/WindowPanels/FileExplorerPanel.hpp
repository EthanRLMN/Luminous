#pragma once

#include <filesystem>

#include "Interface/IWindowPanel.hpp"


class FileExplorerPanel : public IWindowPanel
{
public:
    explicit FileExplorerPanel(Editor* a_editor, const std::string& a_windowIdentifier);

    void Init() override {};
    void Update() override {};
    void Render() override;
    void Destroy() override {};

private:
    std::filesystem::path m_currentDirectory{};
    void OpenTextEditor(const std::filesystem::path& path);
};
