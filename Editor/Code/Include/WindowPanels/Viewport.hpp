#pragma once

#include "Interface/IWindowPanel.hpp"
#include "Rendering/Vulkan/VulkanRenderer.hpp"
#include "Rendering/Vulkan/VulkanDescriptor.hpp"

class Viewport : public IWindowPanel
{
public:
    explicit Viewport(Editor* a_editor, const std::string& a_windowIdentifier) : IWindowPanel(a_editor, a_windowIdentifier) {};

    

    void Init() override {};
    void Update() override {};
    void Draw() override;
    void Destroy() override {};
};
