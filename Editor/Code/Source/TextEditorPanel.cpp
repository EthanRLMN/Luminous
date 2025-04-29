#include "TextEditorPanel.hpp"
#include "imgui.h"

TextEditorPanel::TextEditorPanel(Editor* a_editor, const std::string& a_windowIdentifier)
{
    m_filePath = "";
    m_textBuffer = "";
}

void TextEditorPanel::OpenFile(const std::string& path, const std::string& content)
{
    m_filePath = path;
    m_textBuffer = content;
    p_isOpen = true;
}

void TextEditorPanel::Render()
{
    if (!p_isOpen)
        return;

    ImGui::Begin(p_windowIdentifier.c_str(), &p_isOpen, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Fichier : %s", m_filePath.c_str());
    ImGui::Separator();

    ImGui::InputTextMultiline("##TextEditor", &m_textBuffer, ImVec2(600, 400), ImGuiInputTextFlags_AllowTabInput);

    ImGui::End();
}
