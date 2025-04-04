#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"
#include "Core/GLFW/GLFWwindow.hpp"
#include "Rendering/Vulkan/VulkanInstance.hpp"
#include "Engine.hpp"

class GLFWWindow;
class VulkanInstance;

class Editor
{
public:
    Editor() = default;
    ~Editor();

    void InitEditor();
    void SetupImGui();
    
    int main();

private:
    Engine* m_engine = nullptr;
};