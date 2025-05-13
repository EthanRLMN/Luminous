#pragma once

#include "imgui.h"
#include "ImGuizmo.h"

#include "Editor.hpp"


class Editor;


class IWindowPanel
{
public:
    static constexpr int s_defaultPanelWidth = 600;
    static constexpr int s_defaultPanelHeight = 400;

    inline virtual ~IWindowPanel() = default;

    IWindowPanel(Editor* a_editor, const std::string& a_windowIdentifier) :
        p_editor(a_editor), p_windowIdentifier(a_windowIdentifier) {}

    virtual void Init() = 0;
    virtual void Update() = 0;
    inline virtual void Render() { ImGui::SetNextWindowSize(ImVec2(s_defaultPanelWidth, s_defaultPanelHeight), ImGuiCond_FirstUseEver); };
    virtual void Destroy() = 0;

    inline virtual bool IsOpen() const { return p_isOpen; }
    inline virtual std::string GetWindowIdentifier() const { return p_windowIdentifier; }

protected:
    Editor* p_editor{ nullptr };
    bool p_isOpen{ true };
    std::shared_ptr<Entity> p_isEntitySelected{};
    std::string p_windowIdentifier{ std::to_string(rand() % 100) };
};
