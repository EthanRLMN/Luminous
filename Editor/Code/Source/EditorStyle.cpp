#include "EditorStyle.hpp"
#include "imgui.h"
#include "imgui_internal.h"

void EditorStyle::SetupImGuiStyle()
{
    ImGuiStyle& l_style = ImGui::GetStyle();

    l_style.Alpha = 1.0f;
    l_style.DisabledAlpha = 0.6f;
    l_style.WindowPadding = ImVec2(20.0f, 20.0f);
    l_style.WindowRounding = 11.5f;
    l_style.WindowBorderSize = 0.0f;
    l_style.WindowMinSize = ImVec2(20.0f, 20.0f);
    l_style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    l_style.WindowMenuButtonPosition = ImGuiDir_None;
    l_style.ChildRounding = 9.0f;
    l_style.ChildBorderSize = 1.0f;
    l_style.PopupRounding = 9.0f;
    l_style.PopupBorderSize = 1.0f;
    l_style.FramePadding = ImVec2(20.0f, 4.0f);
    l_style.FrameRounding = 7.5f;
    l_style.FrameBorderSize = 1.0f;
    l_style.ItemSpacing = ImVec2(9.5f, 10.0f);
    l_style.ItemInnerSpacing = ImVec2(9.5f, 1.75f);
    l_style.CellPadding = ImVec2(12.0f, 9.25f);
    l_style.IndentSpacing = 12.0f;
    l_style.ColumnsMinSpacing = 9.0f;
    l_style.ScrollbarSize = 11.5f;
    l_style.ScrollbarRounding = 3.0f;
    l_style.GrabMinSize = 7.5f;
    l_style.GrabRounding = 3.0f;
    l_style.TabRounding = 6.0f;
    l_style.TabBorderSize = 0.0f;
    l_style.ColorButtonPosition = ImGuiDir_Left;
    l_style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    l_style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

    l_style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    l_style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.500f, 0.520f, 0.575f, 1.0f);
    l_style.Colors[ImGuiCol_WindowBg] = ImVec4(0.100f, 0.115f, 0.140f, 1.0f);
    l_style.Colors[ImGuiCol_ChildBg] = ImVec4(0.130f, 0.150f, 0.200f, 1.0f);
    l_style.Colors[ImGuiCol_PopupBg] = ImVec4(0.170f, 0.275f, 0.475f, 1.0f);
    l_style.Colors[ImGuiCol_Border] = ImVec4(0.230f, 0.330f, 0.430f, 1.0f);
    l_style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.700f, 0.700f, 0.700f, 1.0f);
    l_style.Colors[ImGuiCol_FrameBg] = ImVec4(0.135f, 0.165f, 0.200f, 1.0f);
    l_style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.130f, 0.170f, 0.240f, 1.0f);
    l_style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.170f, 0.275f, 0.500f, 1.0f);
    l_style.Colors[ImGuiCol_TitleBg] = ImVec4(0.150f, 0.200f, 0.285f, 1.0f);
    l_style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.240f, 0.400f, 0.700f, 1.0f);
    l_style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.135f, 0.170f, 0.232f, 1.0f);
    l_style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.150f, 0.200f, 0.285f, 1.0f);
    l_style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.300f, 0.330f, 0.400f, 1.0f);
    l_style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.600f, 0.600f, 0.600f, 1.0f);
    l_style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.800f, 0.800f, 0.800f, 1.0f);
    l_style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    l_style.Colors[ImGuiCol_CheckMark] = ImVec4(0.030f, 1.0f, 0.850f, 1.0f);
    l_style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.450f, 0.450f, 0.450f, 1.0f);
    l_style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    l_style.Colors[ImGuiCol_Button] = ImVec4(0.135f, 0.165f, 0.200f, 1.0f);
    l_style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.135f, 0.200f, 0.290f, 1.0f);
    l_style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.230f, 0.400f, 0.700f, 1.0f);
    l_style.Colors[ImGuiCol_Header] = ImVec4(0.150f, 0.165f, 0.200f, 1.0f);
    l_style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.250f, 0.350f, 0.550f, 1.0f);
    l_style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.170f, 0.275f, 0.500f, 1.0f);
    l_style.Colors[ImGuiCol_Separator] = ImVec4(0.700f, 0.700f, 0.700f, 1.0f);
    l_style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.500f, 0.500f, 0.500f, 1.0f);
    l_style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.750f, 0.750f, 0.750f, 1.0f);
    l_style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.660f, 0.750f, 0.750f, 1.0f);
    l_style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.03f, 1.0f, 0.850f, 1.0f);
    l_style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    l_style.Colors[ImGuiCol_Tab] = ImVec4(0.250f, 0.280f, 0.350f, 1.0f);
    l_style.Colors[ImGuiCol_TabHovered] = ImVec4(0.130f, 0.230f, 0.420f, 1.0f);
    l_style.Colors[ImGuiCol_TabActive] = ImVec4(0.170f, 0.275f, 0.500f, 1.0f);
    l_style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.250f, 0.280f, 0.350f, 1.0f);
    l_style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.250f, 0.280f, 0.350f, 1.0f);
    l_style.Colors[ImGuiCol_PlotLines] = ImVec4(0.5215686559677124f, 0.6000000238418579f, 0.7019608020782471f, 1.0f);
    l_style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.03921568766236305f, 0.9803921580314636f, 0.9803921580314636f, 1.0f);
    l_style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.0313725508749485f, 0.9490196108818054f, 0.843137264251709f, 1.0f);
    l_style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
    l_style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.170f, 0.275f, 0.500f, 1.0f);
    l_style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.260f, 0.260f, 0.260f, 1.0f);
    l_style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.375f, 0.375f, 0.375f, 1.0f);
    l_style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.150f, 0.175f, 0.230f, 1.0f);
    l_style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.120f, 0.135f, 0.165f, 1.0f);
    l_style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.9372549057006836f, 0.9372549057006836f, 0.9372549057006836f, 1.0f);
    l_style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
    l_style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.2666666805744171f, 0.2901960909366608f, 1.0f, 1.0f);
    l_style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
    l_style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);
    l_style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);

    if (GImGui && (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_IsSRGB))
        ImGui::ForceStyleColorSpaceConversion(&l_style, true);
}
