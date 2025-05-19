#pragma once

#include "backends/imgui_impl_vulkan.h"

#include "Interface/IWindowPanel.hpp"

#include "InspectorPanel.hpp"
#include "Game/Systems/Camera/CameraEditor.hpp"

class Viewport : public IWindowPanel
{

    struct ViewportImageInfo
    {
        ImVec2 m_position;
        ImVec2 m_size;
    };

public:
    explicit Viewport(Editor* a_editor, const std::string& a_windowIdentifier) : IWindowPanel(a_editor, a_windowIdentifier) {}

    void Init() override;
    void Update() override {};
    void Render() override;
    void Destroy() override {};

    void InitIcons();
    static std::shared_ptr<ITexture> LoadTexture(const Engine* engine, const std::string& path);


private:
    void RenderToolbarButtons();
    void UpdateTextureIfNeeded();
    void RenderGizmo(const ViewportImageInfo& a_imageInfo) const;
    ViewportImageInfo RenderViewportImage() const;

    std::shared_ptr<ITexture> m_iconMove, m_iconRotate, m_iconResize, m_iconPlay, m_iconStop {};
    ImTextureID m_iconMoveID { 0 };
    ImTextureID m_iconRotateID { 0 };
    ImTextureID m_iconResizeID { 0 };
    ImTextureID m_iconPlayID { 0 };
    ImTextureID m_iconStopID { 0 };

    ImVec2 m_lastSize { 0.0f, 0.0f };
    ImTextureID dSets {};

    ImGuizmo::OPERATION m_currentGizmoOperation { ImGuizmo::TRANSLATE };
    CameraEditor m_camera {};
};
