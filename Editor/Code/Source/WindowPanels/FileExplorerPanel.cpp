#include "imgui.h"

#include "WindowPanels/FileExplorerPanel.hpp"
#include "TextEditorPanel.hpp"

#include "Rendering/Vulkan/VulkanTexture.hpp"


static const std::filesystem::path s_AssetPath = "Engine/Assets";
static const std::filesystem::path s_IconPath = "Editor/Assets/Icons";



FileExplorerPanel::FileExplorerPanel(Editor* a_editor, const std::string& a_windowIdentifier) : IWindowPanel(a_editor, a_windowIdentifier)
{
    m_currentDirectory = s_AssetPath;
    m_engine = a_editor->GetEngine();
    m_directoryIconTexture = LoadTexture(m_engine, "Editor/Assets/Icons/DirectoryIcon.png");
    m_fileIconTexture = LoadTexture(m_engine, "Editor/Assets/Icons/FileIcon.png");
}

void FileExplorerPanel::Render()
{
    IWindowPanel::Render();

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
            if (directoryEntry.is_directory())
            {
                ImGui::SameLine();
                ImGui::PushID(filenameString.c_str());
                if (ImGui::ImageButton("Folder", (ImTextureID) (uintptr_t) m_directoryIconTexture->CastVulkan()->GetTextureImageView(), ImVec2(64, 64)))
                {
                    m_currentDirectory /= directoryEntry.path().filename();
                }
                ImGui::PopID();
            } else
            {
                ImGui::SameLine();
                ImGui::PushID(filenameString.c_str());
                if (ImGui::ImageButton("File", (ImTextureID) (uintptr_t) m_fileIconTexture->CastVulkan()->GetTextureImageView(), ImVec2(64, 64)))
                {
                    std::string extension = path.extension().string();

                    if (extension == ".txt" || extension == ".cpp" || extension == ".hpp")
                    {
                        OpenTextEditor(path);
                    }
                }
                ImGui::PopID();
            }
        }

        ImGui::PopStyleColor();
        ImGui::End();
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
    params.m_swapChain = engine->GetSwapChain();
    params.m_commandPool = engine->GetCommandPool();
    params.m_texturePath = path;

    auto texture = std::make_shared<VulkanTexture>();
    texture->CreateTextureImage(params.m_device, params.m_swapChain, params.m_commandPool, path);
    return texture;
}