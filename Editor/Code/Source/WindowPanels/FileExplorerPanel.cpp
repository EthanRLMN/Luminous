#include "WindowPanels/FileExplorerPanel.hpp"

#include <filesystem>
#include <iostream>
#include <string>

#include "Rendering/Vulkan/VulkanRenderer.hpp"
#include "Rendering/Vulkan/VulkanTexture.hpp"
#include "backends/imgui_impl_vulkan.h"


static const std::filesystem::path s_AssetPath = "Engine/Assets";
static const std::filesystem::path s_IconPath = "Editor/Assets/Icons/";


FileExplorerPanel::FileExplorerPanel(Editor* a_editor, const std::string& a_windowIdentifier) : IWindowPanel(a_editor, a_windowIdentifier)
{
    m_currentDirectory = s_AssetPath;
    m_engine = a_editor->GetEngine();
    m_directoryIconTexture = LoadTexture(m_engine, (s_IconPath / "DirectoryIcon.png").string());
    m_fileIconTexture = LoadTexture(m_engine, (s_IconPath / "FileIcon.png").string());
    
    m_directoryIconTexture->CastVulkan()->CreateTextureImageView(m_engine->GetDevice());
    m_fileIconTexture->CastVulkan()->CreateTextureImageView(m_engine->GetDevice());

    m_directoryIconTexture->CastVulkan()->CreateTextureSampler(m_engine->GetDevice());
    m_fileIconTexture->CastVulkan()->CreateTextureSampler(m_engine->GetDevice());

    m_directoryDescriptor = reinterpret_cast<ImTextureID>(ImGui_ImplVulkan_AddTexture(
            m_engine->GetRenderer()->CastVulkan()->GetDefaultTextureSampler(),
            m_directoryIconTexture->CastVulkan()->GetTextureImageView(),
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
            ));

    m_fileDescriptor = reinterpret_cast<ImTextureID>(ImGui_ImplVulkan_AddTexture(
            m_engine->GetRenderer()->CastVulkan()->GetDefaultTextureSampler(),
            m_fileIconTexture->CastVulkan()->GetTextureImageView(),
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
            ));
}


void FileExplorerPanel::Render()
{
    IWindowPanel::Render();

    if (p_isOpen)
    {
        ImGui::Begin(p_windowIdentifier.c_str(), &p_isOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);

        static enum class NewFileType {
            None,
            TextFile,
            CppFile,
            ShaderFile,
            Folder
        } selectedFileType = NewFileType::None;

        static char newFileName[128] = "";
        static bool showInvalidName = false;

        if (ImGui::IsMouseClicked(ImGuiMouseButton_Right) && ImGui::IsWindowHovered())
        {
            ImGui::OpenPopup("FileExplorerContextMenu");
        }

        if (ImGui::BeginPopup("FileExplorerContextMenu"))
        {
            if (ImGui::MenuItem("Create Text File"))
            {
                selectedFileType = NewFileType::TextFile;
            }
            if (ImGui::MenuItem("Create C++ File"))
            {
                selectedFileType = NewFileType::CppFile;
            }
            if (ImGui::MenuItem("Create Shader File"))
            {
                selectedFileType = NewFileType::ShaderFile;
            }
            if (ImGui::MenuItem("Create Folder"))
            {
                selectedFileType = NewFileType::Folder;
            }
            ImGui::EndPopup();
        }

        if (selectedFileType != NewFileType::None)
        {
            ImGui::Spacing();
            ImGui::Text("Enter name for new %s:",
                        selectedFileType == NewFileType::Folder ? "folder" : selectedFileType == NewFileType::TextFile ? "text file"
                                                                     : selectedFileType == NewFileType::CppFile        ? "C++ file"
                                                                     : selectedFileType == NewFileType::ShaderFile     ? "shader file"
                                                                                                                       : "");

            ImGui::InputText("##NewFileNameInput", newFileName, IM_ARRAYSIZE(newFileName));

            if (showInvalidName)
            {
                ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "Invalid or duplicate name.");
            }

            if (ImGui::Button("Create") && strlen(newFileName) > 0)
            {
                std::string nameStr = newFileName;
                std::filesystem::path targetPath = m_currentDirectory;
                std::string fileContent;

                if (nameStr.find_first_of("\\/:*?\"<>|") != std::string::npos)
                {
                    showInvalidName = true;
                } else if (!std::filesystem::exists(targetPath))
                {
                    showInvalidName = true;
                } else
                {
                    switch (selectedFileType)
                    {
                        case NewFileType::TextFile:
                            targetPath /= nameStr + ".txt";
                            break;
                        case NewFileType::CppFile:
                            targetPath /= nameStr + ".cpp";
                            fileContent = "#include <iostream>\n\nint main() {\n    std::cout << \"Hello, World!\" << std::endl;\n    return 0;\n}";
                            break;
                        case NewFileType::ShaderFile:
                            targetPath /= nameStr + ".glsl";
                            fileContent = "// Shader code\n";
                            break;
                        case NewFileType::Folder:
                            targetPath /= nameStr;
                            break;
                        default:
                            break;
                    }

                    if (std::filesystem::exists(targetPath))
                    {
                        showInvalidName = true;
                    } else
                    {
                        try
                        {
                            if (selectedFileType == NewFileType::Folder)
                            {
                                std::filesystem::create_directory(targetPath);
                            } else
                            {
                                std::ofstream ofs(targetPath);
                                ofs << fileContent;
                                ofs.close();
                                OpenTextEditor(targetPath);
                            }
                            selectedFileType = NewFileType::None;
                            std::memset(newFileName, 0, sizeof(newFileName));
                            showInvalidName = false;
                        } catch (const std::exception& e)
                        {
                            std::cerr << "Failed to create: " << e.what() << std::endl;
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
            ImGui::Separator();
        }

        if (m_currentDirectory != std::filesystem::path(s_AssetPath))
        {
            if (ImGui::Button("<"))
            {
                m_currentDirectory = m_currentDirectory.parent_path();
            }
        }

        float padding = 64.0f;
        float thumbnailSize = 64.0f;
        float cellSize = thumbnailSize + padding;
        float panelWidth = ImGui::GetContentRegionAvail().x;
        int columnCount = static_cast<int>(panelWidth / cellSize);
        if (columnCount < 1)
            columnCount = 1;

        ImGui::Columns(columnCount, 0, false);

        for (auto& directoryEntry : std::filesystem::directory_iterator(m_currentDirectory))
        {
            const auto& path = directoryEntry.path();
            auto relativePath = std::filesystem::relative(path, s_AssetPath);
            std::string filenameString = relativePath.filename().string();

            ImGui::PushID(filenameString.c_str());

            ImTextureID icon;
            if (directoryEntry.is_directory())
            {
                icon = m_directoryDescriptor;
            } else
            {
                std::string extension = path.extension().string();
                if (extension == ".png" || extension == ".jpg")
                {
                    icon = GetOrLoadImageThumbnail(path.string());
                } else
                {
                    icon = m_fileDescriptor;
                }
            }

            if (ImGui::ImageButton(filenameString.c_str(), icon, ImVec2(thumbnailSize, thumbnailSize)))
            {
                if (directoryEntry.is_directory())
                {
                    m_currentDirectory /= path.filename();
                } else
                {
                    std::string extension = path.extension().string();
                    if (extension == ".txt" || extension == ".cpp" || extension == ".hpp")
                    {
                        OpenTextEditor(path);
                    }
                }
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

        ImGui::PopStyleColor();
        ImGui::End();
    }
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
    texture->CastVulkan()->CreateTextureSampler(m_engine->GetDevice());

    ImTextureID descriptor = reinterpret_cast<ImTextureID>(ImGui_ImplVulkan_AddTexture(
            m_engine->GetRenderer()->CastVulkan()->GetDefaultTextureSampler(),
            texture->CastVulkan()->GetTextureImageView(),
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL));

    m_thumbnailCache[filepath] = descriptor;
    return descriptor;
}
