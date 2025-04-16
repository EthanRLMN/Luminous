#pragma once

#include "Engine.hpp"

class ImguiWindow;
class VulkanInstance;
class IWindowPanel;

class Editor
{
public:
    Editor() = default;
    ~Editor() = default;

    void Destroy();
    void  Init();
    void SetupImGui() const;

    void Update();
    void Render() const;

    void CreateWindows();
    void DrawWindows() const;
    void DestroyWindows() const;

    void RegisterWindow(IWindowPanel* a_windowPanel) { m_windows.push_back(a_windowPanel); };
    void UnregisterWindow(IWindowPanel* a_windowPanel) { std::erase(m_windows, a_windowPanel); };

    [[nodiscard]] Engine* GetEngine() const { return m_engine; }
    [[nodiscard]] std::vector<IWindowPanel*> GetWindows() const { return m_windows; }
    [[nodiscard]] IWindowPanel* GetWindow(const size_t a_index) const { return m_windows[a_index]; }


private:
    Engine* m_engine = nullptr;
    std::vector<IWindowPanel*> m_windows;
};

