#pragma once

#include <string>
#include "IWindowPanel.hpp"

class TextEditorPanel : public IWindowPanel
{
public:
    TextEditorPanel(Editor* a_editor, const std::string& a_windowIdentifier);

    void OpenFile(const std::string& path, const std::string& content);
    void Render() override;

private:
    std::string m_filePath;
    std::string m_textBuffer;
};
