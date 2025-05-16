#pragma once

#include "Engine.hpp"

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

    void RegisterWindow(IWindowPanel* a_windowPanel);
    void UnregisterWindow(IWindowPanel* a_windowPanel);

    void RequestExit() { m_shouldExit = true; }
    [[nodiscard]] bool ShouldExit() const { return m_shouldExit; }


    [[nodiscard]] Engine* GetEngine() const { return m_engine; }
    [[nodiscard]] std::vector<IWindowPanel*> GetWindows() const { return m_windows; }
    [[nodiscard]] IWindowPanel* GetWindow(const size_t a_index) const { return m_windows[a_index]; }

private:
    Engine* m_engine { nullptr };
    std::vector<IWindowPanel*> m_windows {};

    bool m_shouldExit = false;
};