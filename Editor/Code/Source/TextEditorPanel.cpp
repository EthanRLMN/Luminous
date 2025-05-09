#include "TextEditorPanel.hpp"
#include "imgui.h"

TextEditorPanel::TextEditorPanel(Editor* a_editor, const std::string& a_windowIdentifier) : IWindowPanel(a_editor, a_windowIdentifier)
{
    m_filePath = "";
    m_textBuffer = "";
}

void TextEditorPanel::OpenFile(const std::string& path, const std::string& content)
{
    m_filePath = path;
    m_textBuffer = content;
    p_isOpen = true;

    OpenInVisualStudio(path);
}

void TextEditorPanel::OpenInVisualStudio(const std::string& filePath)
{
    std::string command = "start devenv \"" + filePath + "\"";

    system(command.c_str());
}