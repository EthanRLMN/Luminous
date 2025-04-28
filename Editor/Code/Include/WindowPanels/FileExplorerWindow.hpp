#pragma once

#include <filesystem>
#include <string>
#include "Interface/IWindowPanel.hpp"
#include "Rendering/Vulkan/VulkanDescriptor.hpp"

#include "imgui.h"

class VulkanTexture;
class Editor;

class FileExplorerWindow : public IWindowPanel
{
public:
    explicit FileExplorerWindow(Editor* a_editor, const std::string& a_windowIdentifier);
    ~FileExplorerWindow() override;

    void Init() override {};
    void Update() override {};
    void Draw() override;
    void Destroy() override {};

private:
    bool m_texturesInitialized = false ;
    std::filesystem::path m_currentDirectory{};
    inline static const std::filesystem::path s_AssetPath { "Engine/Assets" };

    ImTextureID m_folderIcon = 0;
    ImTextureID m_fileIcon = 0;

    VulkanTexture* m_folderTexture = nullptr;
    VulkanTexture* m_fileTexture = nullptr;
    VulkanDescriptor* m_folderDescriptor = nullptr;
    VulkanDescriptor* m_fileDescriptor = nullptr;

    Engine* m_engine { nullptr };
};
