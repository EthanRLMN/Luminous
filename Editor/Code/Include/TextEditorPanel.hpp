#pragma once

#include <string>
#include "Editor.hpp"
#include "Interface/IWindowPanel.hpp"


class TextEditorPanel : public IWindowPanel
{
public:
    TextEditorPanel(Editor* a_editor, const std::string& a_windowIdentifier);

    void OpenFile(const std::string& path, const std::string& content);
    void OpenInVisualStudio(const std::string& filePath);
    
    void Init() {};
    void Update() {};
    void Render() {};
    void Destroy() {};


private:
    std::string m_filePath;
    std::string m_textBuffer;
    bool p_isOpen = false;
};
