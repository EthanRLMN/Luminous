#pragma once

#include "Engine.hpp"

class ImguiWindow;
class GLFWWindow;
class VulkanInstance;

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

    [[nodiscard]] Engine* GetEngine() const { return m_engine; }
    [[nodiscard]] ImguiWindow* GetImguiWindow() const { return m_imguiWindow; }

private:
    Engine* m_engine = nullptr;
    ImguiWindow* m_imguiWindow = nullptr;
};
