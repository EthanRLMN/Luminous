#include "WindowPanels/FileExplorerPanel.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Rendering/Vulkan/VulkanRenderer.hpp"
#include "Rendering/Vulkan/VulkanTexture.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "backends/imgui_impl_vulkan.h"

static const std::filesystem::path s_AssetPath = "Engine/Assets";
static const std::filesystem::path s_IconPath = "Editor/Assets/Icons/";

FileExplorerPanel::FileExplorerPanel(Editor* a_editor, const std::string& a_windowIdentifier) :
    IWindowPanel(a_editor, a_windowIdentifier)
{
    m_currentDirectory = s_AssetPath;
    m_engine = a_editor->GetEngine();

    m_directoryIconTexture = LoadTexture(m_engine, (s_IconPath / "DirectoryIcon.png").string());
    m_fileIconTexture = LoadTexture(m_engine, (s_IconPath / "FileIcon.png").string());

    m_directoryIconTexture->CastVulkan()->CreateTextureImageView(m_engine->GetDevice());
    m_fileIconTexture->CastVulkan()->CreateTextureImageView(m_engine->GetDevice());

    m_directoryDescriptor = reinterpret_cast<ImTextureID>(ImGui_ImplVulkan_AddTexture(
            ResourceManager::GetInstance().GetStandardSampler(),
            m_directoryIconTexture->CastVulkan()->GetTextureImageView(),
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL));

    m_fileDescriptor = reinterpret_cast<ImTextureID>(ImGui_ImplVulkan_AddTexture(
            ResourceManager::GetInstance().GetStandardSampler(),
            m_fileIconTexture->CastVulkan()->GetTextureImageView(),
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL));
}

void FileExplorerPanel::Render()
{
    IWindowPanel::Render();

    if (!p_isOpen)
        return;

    ImGui::Begin(p_windowIdentifier.c_str(), &p_isOpen, ImGuiWindowFlags_NoCollapse);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);

    ImVec2 fullRegion = ImGui::GetContentRegionAvail();
    float leftPanelWidth = 250.0f;

    ImGui::BeginChild("LeftPanel", ImVec2(leftPanelWidth, 0), true);
    DrawDirectoryTree(s_AssetPath);
    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("RightPanel", ImVec2(0, 0), true);
    DrawDirectoryContent();
    ImGui::EndChild();

    ImGui::PopStyleColor();
    ImGui::End();
}

void FileExplorerPanel::DrawDirectoryTree(const std::filesystem::path& directory)
{
    for (const auto& entry : std::filesystem::directory_iterator(directory))
    {
        if (!entry.is_directory())
            continue;

        const auto& path = entry.path();
        std::string name = path.filename().string();

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
        if (path == m_currentDirectory)
            flags |= ImGuiTreeNodeFlags_Selected;

        bool opened = ImGui::TreeNodeEx(name.c_str(), flags);

        if (ImGui::IsItemClicked())
            m_currentDirectory = path;

        if (opened)
        {
            DrawDirectoryTree(path);
            ImGui::TreePop();
        }
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FILE_DRAG"))
            {
                const char* sourcePath = static_cast<const char*>(payload->Data);
                std::filesystem::path destinationPath = path / std::filesystem::path(sourcePath).filename();

                try
                {
                    std::filesystem::rename(sourcePath, destinationPath);
                } catch (const std::exception& e)
                {
                    std::cerr << "Moving Error :" << e.what() << std::endl;
                }
            }
            ImGui::EndDragDropTarget();
        }
    }
}

void FileExplorerPanel::DrawDirectoryContent()
{
    static enum class NewFileType { None,
                                    TextFile,
                                    CppFile,
                                    Folder } selectedFileType = NewFileType::None;
    static char newFileName[128] = "";
    static bool showInvalidName = false;

    static bool renaming = false;
    static std::filesystem::path renamePath;
    static char renameBuffer[128] = "";
    static bool showRenameInvalid = false;

    static std::filesystem::path rightClickedPath;

    if (m_currentDirectory != s_AssetPath)
    {
        if (ImGui::Button("< Back"))
            m_currentDirectory = m_currentDirectory.parent_path();
    }

    float padding = 64.0f;
    float thumbnailSize = 64.0f;
    float cellSize = thumbnailSize + padding;
    float panelWidth = ImGui::GetContentRegionAvail().x;
    int columnCount = static_cast<int>(panelWidth / cellSize);
    if (columnCount < 1)
        columnCount = 1;

    ImGui::Columns(columnCount, 0, false);
    bool itemRightClicked = false;

    for (auto& entry : std::filesystem::directory_iterator(m_currentDirectory))
    {
        const auto& path = entry.path();
        auto relativePath = std::filesystem::relative(path, s_AssetPath);
        std::string filenameString = relativePath.filename().string();

        ImGui::PushID(filenameString.c_str());

        ImTextureID icon = entry.is_directory() ? m_directoryDescriptor : (path.extension() == ".png" || path.extension() == ".jpg") ? GetOrLoadImageThumbnail(path.string())
                                                                                                                                     : m_fileDescriptor;

        if (ImGui::ImageButton(filenameString.c_str(), icon, ImVec2(thumbnailSize, thumbnailSize)))
        {
            if (entry.is_directory())
                m_currentDirectory /= path.filename();
            else if (path.extension() == ".txt" || path.extension() == ".cpp" || path.extension() == ".hpp")
                OpenTextEditor(path);
        }

        if (entry.is_directory())
        {
            if (ImGui::BeginDragDropTarget())
            {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FILE_DRAG"))
                {
                    const char* sourcePath = static_cast<const char*>(payload->Data);
                    std::filesystem::path destinationPath = path / std::filesystem::path(sourcePath).filename();

                    try
                    {
                        std::filesystem::rename(sourcePath, destinationPath);
                    } catch (const std::exception& e)
                    {
                        std::cerr << "Moving Error : " << e.what() << std::endl;
                    }
                }
                ImGui::EndDragDropTarget();
            }
        }


        if (ImGui::BeginPopupContextItem("ItemContextMenu"))
        {
            rightClickedPath = path;

            if (ImGui::MenuItem("Rename"))
            {
                renaming = true;
                renamePath = rightClickedPath;
                std::memset(renameBuffer, 0, sizeof(renameBuffer));
                strncpy_s(renameBuffer, renamePath.filename().string().c_str(), sizeof(renameBuffer) - 1);
                showRenameInvalid = false;
            }

            if (ImGui::MenuItem("Delete"))
            {
                try
                {
                    if (std::filesystem::is_directory(rightClickedPath))
                        std::filesystem::remove_all(rightClickedPath);
                    else
                        std::filesystem::remove(rightClickedPath);
                } catch (const std::exception& e)
                {
                    std::cerr << "Erreur suppression : " << e.what() << std::endl;
                }
            }

            ImGui::EndPopup();
        }

        if (ImGui::BeginDragDropSource())
        {
            std::string fullPath = path.string();
            ImGui::SetDragDropPayload("FILE_DRAG", fullPath.c_str(), fullPath.size() + 1);
            ImGui::Text("Drag: %s", filenameString.c_str());
            ImGui::EndDragDropSource();
        }

        ImGui::TextWrapped("%s", filenameString.c_str());
        ImGui::NextColumn();
        ImGui::PopID();
    }

    ImGui::Columns(1);

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right) && ImGui::IsWindowHovered() && !itemRightClicked)
        ImGui::OpenPopup("FileExplorerCreatePopup");

    if (ImGui::BeginPopup("FileExplorerCreatePopup"))
    {
        if (ImGui::MenuItem("Create Text File"))
            selectedFileType = NewFileType::TextFile;
        if (ImGui::MenuItem("Create C++ File"))
            selectedFileType = NewFileType::CppFile;
        if (ImGui::MenuItem("Create Folder"))
            selectedFileType = NewFileType::Folder;
        ImGui::EndPopup();
    }

    if (selectedFileType != NewFileType::None)
    {
        ImGui::Spacing();
        ImGui::Text("New %s name:",
                    selectedFileType == NewFileType::Folder ? "folder" : selectedFileType == NewFileType::TextFile ? "text file"
                                                                                                                   : "C++ file");

        ImGui::InputText("##NewFileNameInput", newFileName, IM_ARRAYSIZE(newFileName));
        if (showInvalidName)
            ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "Invalid or duplicate name.");

        if (ImGui::Button("Create") && strlen(newFileName) > 0)
        {
            std::string nameStr = newFileName;
            std::filesystem::path targetPath = m_currentDirectory;
            std::string fileContent;

            if (nameStr.find_first_of("\\/:*?\"<>|") != std::string::npos)
                showInvalidName = true;
            else
            {
                switch (selectedFileType)
                {
                    case NewFileType::TextFile:
                        targetPath /= nameStr + ".txt";
                        break;
                    case NewFileType::CppFile:
                        targetPath /= nameStr + ".cpp";
                        break;
                    case NewFileType::Folder:
                        targetPath /= nameStr;
                        break;
                    default:
                        break;
                }

                if (std::filesystem::exists(targetPath))
                    showInvalidName = true;
                else
                {
                    try
                    {
                        if (selectedFileType == NewFileType::Folder)
                            std::filesystem::create_directory(targetPath);
                        else
                        {
                            std::ofstream ofs(targetPath);
                            ofs << fileContent;
                        }
                        OpenTextEditor(targetPath);
                        selectedFileType = NewFileType::None;
                        std::memset(newFileName, 0, sizeof(newFileName));
                        showInvalidName = false;
                    } catch (...)
                    {
                        showInvalidName = true;
                    }
                }
            }
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            selectedFileType = NewFileType::None;
            std::memset(newFileName, 0, sizeof(newFileName));
            showInvalidName = false;
        }
    }

    if (renaming)
    {
        ImGui::Separator();
        ImGui::Text("Rename \"%s\" to:", renamePath.filename().string().c_str());
        ImGui::InputText("##RenameInput", renameBuffer, IM_ARRAYSIZE(renameBuffer));

        if (showRenameInvalid)
            ImGui::TextColored(ImVec4(1, 0.3f, 0.3f, 1), "Invalid or duplicate name.");

        if (ImGui::Button("OK"))
        {
            std::string newName = renameBuffer;
            std::filesystem::path newPath = renamePath.parent_path() / newName;

            if (newName.empty() || newName.find_first_of("\\/:*?\"<>|") != std::string::npos || std::filesystem::exists(newPath))
                showRenameInvalid = true;
            else
            {
                try
                {
                    std::filesystem::rename(renamePath, newPath);
                    renaming = false;
                    showRenameInvalid = false;
                    std::memset(renameBuffer, 0, sizeof(renameBuffer));
                } catch (...)
                {
                    showRenameInvalid = true;
                }
            }
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            renaming = false;
            showRenameInvalid = false;
            std::memset(renameBuffer, 0, sizeof(renameBuffer));
        }
    }
}

void FileExplorerPanel::OpenTextEditor(const std::filesystem::path& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Impossible d'ouvrir le fichier : " << path << std::endl;
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string fileContent = buffer.str();
    file.close();

    m_textEditorPanel = std::make_unique<TextEditorPanel>(p_editor, "TextEditor_" + path.filename().string());
    m_textEditorPanel->OpenFile(path.string(), fileContent);
}

std::shared_ptr<ITexture> LoadTexture(Engine* engine, const std::string& path)
{
    IResourceParams params{};
    params.m_device = engine->GetDevice();
    params.m_commandPool = engine->GetCommandPool();
    params.m_texturePath = path;

    auto texture = std::make_shared<VulkanTexture>();
    texture->CreateTextureImage(params.m_device, params.m_commandPool, params.m_texturePath);
    return texture;
}

ImTextureID FileExplorerPanel::GetOrLoadImageThumbnail(const std::string& filepath)
{
    if (m_thumbnailCache.find(filepath) != m_thumbnailCache.end())
        return m_thumbnailCache[filepath];

    auto texture = LoadTexture(m_engine, filepath);
    texture->CastVulkan()->CreateTextureImageView(m_engine->GetDevice());

    ImTextureID descriptor = reinterpret_cast<ImTextureID>(ImGui_ImplVulkan_AddTexture(
            ResourceManager::GetInstance().GetStandardSampler(),
            texture->CastVulkan()->GetTextureImageView(),
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL));

    m_thumbnailCache[filepath] = descriptor;
    return descriptor;
}

void FileExplorerPanel::Destroy()
{
    if (m_directoryIconTexture)
    {
        m_directoryIconTexture->CastVulkan()->Destroy(m_engine->GetDevice());
        m_directoryIconTexture.reset();
    }

    if (m_fileIconTexture)
    {
        m_fileIconTexture->CastVulkan()->Destroy(m_engine->GetDevice());
        m_fileIconTexture.reset();
    }

    m_thumbnailCache.clear();
}
