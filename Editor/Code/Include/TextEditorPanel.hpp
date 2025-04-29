#pragma once

#include <string>
#include "Editor.hpp"
#include "IWindow.hpp"

class TextEditorPanel : public IWindow
{
public:
    TextEditorPanel(Editor* a_editor, const std::string& a_windowIdentifier);

    void OpenFile(const std::string& path, const std::string& content);
    void Render();

private:
    std::string m_filePath;
    std::string m_textBuffer;
};
