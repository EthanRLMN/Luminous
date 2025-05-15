#pragma once

#include "Engine.hpp"


class ImguiWindow;
class VulkanInstance;
class IWindowPanel;


class Editor
{
public:
    Editor() = default;
    ~Editor();

    void Destroy();
    void Init();
    void SetupImGui() const;

    void Update();
    void Render() const;

    void CreateWindowPanels();
    void RenderWindowPanels() const;
    void DestroyWindowPanels();

    void RegisterWindow(IWindowPanel* a_windowPanel) { m_windows.push_back(a_windowPanel); };
    void UnregisterWindow(IWindowPanel* a_windowPanel);
    void SetSelectedEntity(const std::shared_ptr<Entity>& entity) { m_selectedEntity = entity; }

    void RequestExit() { m_shouldExit = true; }
    bool ShouldExit() const { return m_shouldExit; }


    [[nodiscard]] Engine* GetEngine() const { return m_engine; }
    [[nodiscard]] std::vector<IWindowPanel*> GetWindows() const { return m_windows; }
    [[nodiscard]] IWindowPanel* GetWindow(const size_t a_index) const { return m_windows[a_index]; }
    [[nodiscard]] std::shared_ptr<Entity> GetSelectedEntity() const { return m_selectedEntity; }


    std::shared_ptr<Entity> m_selectedEntity;

private:
    Engine* m_engine { nullptr };
    std::vector<IWindowPanel*> m_windows {};

    bool m_shouldExit = false;
};