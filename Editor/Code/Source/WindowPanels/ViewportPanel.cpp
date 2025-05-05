#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

#include "WindowPanels/ViewportPanel.hpp"


void Viewport::Render()
{
    IWindowPanel::Render();

    ImGui::Begin(p_windowIdentifier.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);

    VulkanRenderer* l_renderer = p_editor->GetEngine()->GetRenderingDraw()->CastVulkan();
    if (dSets && l_renderer->bReloadImage)
    {
        ImGui_ImplVulkan_RemoveTexture(dSets);

        dSets = ImGui_ImplVulkan_AddTexture(l_renderer->GetViewportImageSampler(), l_renderer->GetViewportImageView(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
        l_renderer->bReloadImage = false;
        l_renderer->bUsable = false;
    }


    VkExtent2D l_extent = p_editor->GetEngine()->GetSwapChain()->CastVulkan()->GetSwapChainExtent();

    float l_texWidth = static_cast<float>(l_extent.width);
    float l_texHeight = static_cast<float>(l_extent.height);
    float l_aspectRatio = l_texWidth / l_texHeight;

    ImVec2 l_avail = ImGui::GetContentRegionAvail();
    float l_fitWidth = l_avail.x;
    float l_fitHeight = l_fitWidth / l_aspectRatio;
    
    if (l_fitHeight > l_avail.y)
    {
        l_fitHeight = l_avail.y;
        l_fitWidth = l_fitHeight * l_aspectRatio;
    }

    const ImVec2 l_imageSize(l_fitWidth, l_fitHeight);

    const ImVec2 l_screenPos = ImGui::GetCursorScreenPos();
    const float l_offsetX = (l_avail.x - l_imageSize.x) * 0.5f;
    const float l_offsetY = (l_avail.y - l_imageSize.y) * 0.5f;

    ImGui::SetCursorScreenPos(ImVec2(l_screenPos.x + l_offsetX, l_screenPos.y + l_offsetY));


    ImGui::Image(reinterpret_cast<ImTextureID>(dSets), l_imageSize);
    ImGui::End();
}
