#pragma once

#include "TextEditorPanel.hpp"
#include "Interface/IWindowPanel.hpp"

class FileExplorerPanel : public IWindowPanel
{
public:
    FileExplorerPanel(Editor* a_editor, const std::string& a_windowIdentifier);
    virtual ~FileExplorerPanel() override = default;

    void Init() override {}
    void Update() override {}
    void Render() override;
    void Destroy() override;

private:
    void DrawDirectoryTree(const std::filesystem::path& directory);
    void DrawDirectoryTreeRecursive(const std::filesystem::path& directory);
    void DrawDirectoryContent();
    void OpenTextEditor(const std::filesystem::path& path);
    void HandleRenamePopup();
    ImTextureID GetOrLoadImageThumbnail(const std::string& filepath);


    Engine* m_engine = nullptr;

    std::filesystem::path m_currentDirectory;

    std::shared_ptr<ITexture> m_directoryIconTexture;
    std::shared_ptr<ITexture> m_fileIconTexture;

    ImTextureID m_directoryDescriptor = NULL;
    ImTextureID m_fileDescriptor = NULL;

    std::unordered_map<std::string, ImTextureID> m_thumbnailCache;

    std::unique_ptr<TextEditorPanel> m_textEditorPanel;

    bool m_renaming = false;
    std::filesystem::path m_renamePath;
    char m_renameBuffer[128] = {};
    bool m_showRenameInvalid = false;

    bool openRenamePopup = false;
};

std::shared_ptr<ITexture> LoadTexture(Engine* engine, const std::string& path);
