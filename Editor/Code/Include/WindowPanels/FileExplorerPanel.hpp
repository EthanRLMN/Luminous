#pragma once

#include <filesystem>
#include "GLFW/glfw3.h"

#include "Interface/IWindowPanel.hpp"
#include "TextEditorPanel.hpp"
#include "stb_image.h"


class FileExplorerPanel : public IWindowPanel
{
public:
    explicit FileExplorerPanel(Editor* a_editor, const std::string& a_windowIdentifier);

    void Init() override {};
    void Update() override {};
    void Render() override;
    void Destroy() override;

private:
    std::filesystem::path m_currentDirectory{};
    void OpenTextEditor(const std::filesystem::path& path);

    Engine* m_engine{ nullptr };

    std::unique_ptr<TextEditorPanel> m_textEditorPanel;
    std::shared_ptr<ITexture> m_directoryIconTexture;
    std::shared_ptr<ITexture> m_fileIconTexture;

    ImTextureID m_directoryDescriptor = NULL;
    ImTextureID m_fileDescriptor = NULL;
};

std::shared_ptr<ITexture> LoadTexture(Engine* engine, const std::string& path);
