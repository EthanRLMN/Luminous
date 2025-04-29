#include "imgui.h"

#include "WindowPanels/FileExplorerPanel.hpp"
#include "TextEditorPanel.hpp"


static const std::filesystem::path s_AssetPath = "Engine/Assets";


FileExplorerPanel::FileExplorerPanel(Editor* a_editor, const std::string& a_windowIdentifier) : IWindowPanel(a_editor, a_windowIdentifier)
{
    m_currentDirectory = s_AssetPath;
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
                if (ImGui::Button(filenameString.c_str()))
                {
                    m_currentDirectory /= directoryEntry.path().filename();
                }
            } else
            {
                if (ImGui::Button(filenameString.c_str()))
                {
                    std::string extension = path.extension().string();

                    if (extension == ".txt")
                    {
                        OpenTextEditor(path);
                    } 
                    /* else if (extension == ".png" || extension == ".jpg")
                    {
                        OpenImageViewer(path);
                    } 
                    else if (extension == ".fbx" || extension == ".obj")
                    {
                        Open3DModelViewer(path);
                    }*/
                }
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
    
    //TextEditorPanel;
}
