#include "imgui.h"
#include "imgui/backends/imgui_impl_vulkan.h"

#include "TextEditorPanel.hpp"
#include "WindowPanels/FileExplorerPanel.hpp"

#include "Rendering/Vulkan/VulkanTexture.hpp"


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

    m_directoryIconTexture->CastVulkan()->CreateTextureSampler(m_engine->GetDevice());
    m_fileIconTexture->CastVulkan()->CreateTextureSampler(m_engine->GetDevice());

    m_directoryDescriptor = (ImTextureID) ImGui_ImplVulkan_AddTexture(
            m_engine->GetDefaultSampler(),
            m_directoryIconTexture->CastVulkan()->GetTextureImageView(),
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
    );

    m_fileDescriptor = (ImTextureID) ImGui_ImplVulkan_AddTexture(
            m_engine->GetDefaultSampler(),
            m_fileIconTexture->CastVulkan()->GetTextureImageView(),
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
    );
}

FileExplorerPanel::~FileExplorerPanel()
{
    m_directoryIconTexture->CastVulkan()->Destroy(m_engine->GetDevice());
    m_fileIconTexture->CastVulkan()->Destroy(m_engine->GetDevice());
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

        float padding = 64.0f;
        float thumbnailSize = 64.0f;
        float cellSize = thumbnailSize + padding;
        float panelWidth = ImGui::GetContentRegionAvail().x;
        int columnCount = (int) (panelWidth / cellSize);
        if (columnCount < 1)
            columnCount = 1;

        ImGui::Columns(columnCount, 0, false);

        for (auto& directoryEntry : std::filesystem::directory_iterator(m_currentDirectory))
        {
            const auto& path = directoryEntry.path();
            auto relativePath = std::filesystem::relative(path, s_AssetPath);
            std::string filenameString = relativePath.filename().string();

            ImGui::PushID(filenameString.c_str());

            ImTextureID icon = directoryEntry.is_directory() ? m_directoryDescriptor : m_fileDescriptor;

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

            ImGui::TextWrapped("%s", filenameString.c_str());

            ImGui::NextColumn();
            ImGui::PopID();
        }
        ImGui::Columns(1);
    }

    ImGui::PopStyleColor();
    ImGui::End();
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
    texture->CreateTextureImage(params.m_device, params.m_swapChain, params.m_commandPool, params.m_texturePath);
    return texture;
}