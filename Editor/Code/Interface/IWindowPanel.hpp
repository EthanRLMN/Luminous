#pragma once
#include "Editor.hpp"

class Editor;

class IWindowPanel
{
public:
    virtual ~IWindowPanel() { delete p_editor; };
    explicit IWindowPanel(Editor* a_editor, const std::string& a_windowIdentifier)
    {
        if (a_editor)
        {
            p_editor = { a_editor };
            p_editor->RegisterWindow(this);
        }
        p_windowIdentifier = { a_windowIdentifier };
    }
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Destroy() = 0;

    [[nodiscard]] virtual bool IsOpen() const { return p_isOpen; }
    [[nodiscard]] virtual std::string GetWindowIdentifier() const { return p_windowIdentifier; }

protected:
    Editor* p_editor{ nullptr };
    bool p_isOpen{ true };
    std::string p_windowIdentifier{ std::to_string(rand() % 100) };
};
