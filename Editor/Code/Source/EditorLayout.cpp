#include "EditorLayout.hpp"

#include <imgui.h>

#include "Logger.hpp"


void EditorLayout::LoadEditorLayout()
{
    ImGuiIO& l_io = ImGui::GetIO();
    l_io.IniFilename = nullptr;

    try
    {
        const std::string l_editorFilePath = LoadIniFileToString("Editor/Assets/EditorConfig.ini");
        ImGui::LoadIniSettingsFromMemory(l_editorFilePath.c_str(), l_editorFilePath.size());
    } catch (const std::exception& e) 
    { 
        DEBUG_LOG_ERROR("Cannot load ini file {}", e.what()); 
    }
}


std::string EditorLayout::LoadIniFileToString(const std::string& a_filePath)
{
    std::ifstream l_file(a_filePath);
    if (!l_file)
        throw std::runtime_error("Unable to open file : " + a_filePath);

    std::stringstream l_buffer{ };
    l_buffer << l_file.rdbuf();
    return l_buffer.str();
}