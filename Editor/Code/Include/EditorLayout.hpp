#pragma once
#include <string>

class EditorLayout
{
public:
    EditorLayout() = default;
    ~EditorLayout() = default;

    static void LoadEditorLayout();

private:
    const std::string m_iniFile { "" };

    static std::string LoadIniFileToString(const std::string& a_filePath);
};
