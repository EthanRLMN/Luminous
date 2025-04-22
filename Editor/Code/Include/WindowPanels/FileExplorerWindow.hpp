#pragma once

#include <filesystem>
#include <string>
#include "Interface/IWindowPanel.hpp"

class VulkanTexture;
class Editor;

class FileExplorerWindow : public IWindowPanel
{
public:
    explicit FileExplorerWindow(Editor* a_editor, const std::string& a_windowIdentifier) :
        IWindowPanel(a_editor, a_windowIdentifier),
        m_currentDirectory(s_AssetPath) {}

    void Init() override {};
    void Update() override {};
    void Draw() override;
    void Destroy() override {};

private:
    std::filesystem::path m_currentDirectory;
    inline static const std::filesystem::path s_AssetPath = "Engine/Assets";

    ImTextureID m_folderIcon = 0;
    ImTextureID m_fileIcon = 0;

    bool m_texturesInitialized = false;

    Editor* m_editor;
};
