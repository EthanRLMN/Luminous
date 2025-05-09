#include "EditorLayout.hpp"

#include "Logger.hpp"
#include "imgui.h"

void EditorLayout::LoadEditorLayout()
{
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;

    try
    {
        const std::string iniContents = LoadIniFileToString("Editor/Assets/EditorConfig.ini");
        ImGui::LoadIniSettingsFromMemory(iniContents.c_str(), iniContents.size());
    } catch (const std::exception& e) 
    { 
        DEBUG_LOG_ERROR("Cannot load ini file {}", e.what()); 
    }
}

std::string EditorLayout::LoadIniFileToString(const std::string& a_filePath)
{
    std::ifstream file(a_filePath);
    if (!file)
        throw std::runtime_error("Unable to open file : " + a_filePath);

    std::stringstream l_buffer{ };
    l_buffer << file.rdbuf();
    return l_buffer.str();
}
