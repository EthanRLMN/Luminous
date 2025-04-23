#pragma once

#include <filesystem>
#include <string>
#include "Interface/IWindowPanel.hpp"
#include "ResourceManager/ResourceManager.hpp"

#include "imgui.h"

class VulkanTexture;
class Editor;

class FileExplorerWindow : public IWindowPanel
{
public:
    explicit FileExplorerWindow(Editor* a_editor, IResourceManager* a_resourceManager, const std::string& a_windowIdentifier) :
        IWindowPanel(a_editor, a_windowIdentifier),
        m_currentDirectory(s_AssetPath),
        m_editor(a_editor),
        m_resourceManager(a_resourceManager)
    {}

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
    IResourceManager* m_resourceManager;
};
