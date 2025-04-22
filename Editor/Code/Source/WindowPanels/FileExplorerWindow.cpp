#include "WindowPanels/FileExplorerWindow.hpp"
#include "Rendering/Vulkan/VulkanDevice.hpp"
#include "Editor.hpp"

#include "imgui.h"

void FileExplorerWindow::Draw()
{
    if (!m_texturesInitialized)
    {
        IResourceParams folderParams;
        folderParams.m_texturePath = "Assets/Icons/FolderIcon.png";
        folderParams.m_device = m_editor->GetEngine()->GetDevice();
        folderParams.m_swapChain = m_editor->GetEngine()->GetSwapChain();

        auto* folderTexture = new VulkanTexture();
        if (folderTexture->Create(IResourceManager::GetResource(), folderParams))
        {
            m_folderIcon = reinterpret_cast<ImTextureID>(folderTexture->GetTextureImageView());
        }

        IResourceParams fileParams;
        fileParams.m_texturePath = "Assets/Icons/FileIcon.png";
        fileParams.m_device = folderParams.m_device;
        fileParams.m_swapChain = folderParams.m_swapChain;

        auto* fileTexture = new VulkanTexture();
        if (fileTexture->Create(IResourceManager::GetResource, fileParams))
        {
            m_fileIcon = reinterpret_cast<ImTextureID>(fileTexture->GetTextureImageView());
        }

        m_texturesInitialized = true;
    }

    // ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
    ImGui::SetNextWindowSize(ImVec2(1920.f, 600.f), ImGuiCond_FirstUseEver);

    if (p_isOpen)
    {
        ImGui::Begin(p_windowIdentifier.c_str(), &p_isOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);

        if (m_currentDirectory != std::filesystem::path(s_AssetPath))
        {
            if (ImGui::Button("<"))
            {
                m_currentDirectory = m_currentDirectory.parent_path();
            }
        }

        for (auto& directoryEntry : std::filesystem::directory_iterator(m_currentDirectory))
        {
            const auto& path = directoryEntry.path();
            auto relativePath = std::filesystem::relative(path, s_AssetPath);
            std::string filenameString = relativePath.filename().string();

            ImTextureID icon = directoryEntry.is_directory() ? m_folderIcon : m_fileIcon;

            if (ImGui::ImageButton("Folder", icon, ImVec2(64, 64)))
            {
                m_currentDirectory /= directoryEntry.path().filename();
            }
            ImGui::SameLine();
            ImGui::Text("%s", filenameString.c_str());
        }
        ImGui::PopStyleColor();
        ImGui::End();
    }
}
