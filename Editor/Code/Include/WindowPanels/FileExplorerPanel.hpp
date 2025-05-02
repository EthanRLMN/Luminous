#pragma once

#include <filesystem>
#include "GLFW/glfw3.h"

#include "Interface/IWindowPanel.hpp"
#include "stb_image.h"
#include "TextEditorPanel.hpp"


class FileExplorerPanel : public IWindowPanel
{
public:
    explicit FileExplorerPanel(Editor* a_editor, const std::string& a_windowIdentifier);
    ~FileExplorerPanel() override;

    void Init() override {};
    void Update() override {};
    void Render() override;
    void Destroy() override {};

private:
    std::filesystem::path m_currentDirectory{};
    void OpenTextEditor(const std::filesystem::path& path);

    Engine* m_engine{ nullptr };

    std::unique_ptr<TextEditorPanel> m_textEditorPanel;
    ITexture* m_directoryIconTexture = nullptr;
    ITexture* m_fileIconTexture = nullptr;


    ITexture* LoadTexture(Engine* engine, const std::string& path);
};
