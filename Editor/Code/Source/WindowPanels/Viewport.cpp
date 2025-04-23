#include "imgui.h"

#include "WindowPanels/Viewport.hpp"



void Viewport::Draw()
{
    ImGui::SetNextWindowPos(ImVec2(5, 70), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(1935, 880), ImGuiCond_FirstUseEver);

    ImGui::Begin(p_windowIdentifier.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 5.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);

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

    ImVec2 l_imageSize(l_fitWidth, l_fitHeight);

    ImVec2 l_screenPos = ImGui::GetCursorScreenPos();
    float l_offsetX = (l_avail.x - l_imageSize.x) * 0.5f;
    float l_offsetY = (l_avail.y - l_imageSize.y) * 0.5f;

    ImGui::SetCursorScreenPos(ImVec2(l_screenPos.x + l_offsetX, l_screenPos.y + l_offsetY));


    ImGui::Image((ImTextureID) dSets, l_imageSize);

    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    ImGui::End();
}
