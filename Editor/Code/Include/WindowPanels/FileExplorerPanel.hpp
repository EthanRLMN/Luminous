#pragma once

#include <filesystem>

#include "Interface/IWindowPanel.hpp"
#include "TextEditorPanel.hpp"


class FileExplorerPanel : public IWindowPanel
{
public:
    explicit FileExplorerPanel(Editor* a_editor, const std::string& a_windowIdentifier);
    ~FileExplorerPanel() override {};

    void Init() override {};
    void Update() override {};
    void Render() override;
    void Destroy() override {};

private:
    std::filesystem::path m_currentDirectory{};
    void OpenTextEditor(const std::filesystem::path& path);

    std::unique_ptr<TextEditorPanel> m_textEditorPanel;
};
