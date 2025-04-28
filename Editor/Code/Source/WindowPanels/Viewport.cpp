#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

#include "WindowPanels/Viewport.hpp"



void Viewport::Draw()
{
    IWindowPanel::Draw();

    ImGui::Begin(p_windowIdentifier.c_str(), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground);
    
    ISwapChain* l_swapchain = p_editor->GetEngine()->GetSwapChain();

    

    

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

    const ImVec2 l_avail = ImGui::GetContentRegionAvail();
    const VkExtent2D l_currentSize = {
        static_cast<uint32_t>(l_avail.x),
        static_cast<uint32_t>(l_avail.y)
    };


    if (m_lastSize.x != l_currentSize.width || m_lastSize.y != l_currentSize.height)
    {
        //p_editor->GetEngine()->GetRenderingDraw()->CastVulkan()->SetViewportSize(static_cast<float>(l_currentSize.width), static_cast<float>(l_currentSize.height));
        //p_editor->GetEngine()->GetRenderingDraw()->CastVulkan()->ReCreateViewportImage(p_editor->GetEngine()->GetDevice(), l_swapchain);
        //m_lastSize = ImGui::GetContentRegionAvail();
    }

    if (dSets)
    {
        //ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        //ImGui::SetCursorPos((viewportSize - ImVec2(static_cast<float>(l_currentSize.width), static_cast<float>(l_currentSize.height))) * 0.5f);
        //ImGui::Image(reinterpret_cast<ImTextureID>(dSets), ImVec2(static_cast<float>(l_currentSize.width), static_cast<float>(l_currentSize.height)));
    }





    ImGui::Image(reinterpret_cast<ImTextureID>(dSets), viewportPanelSize);
    ImGui::End();
}
