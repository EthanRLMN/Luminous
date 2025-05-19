#include "imgui.h"


#include "WindowPanels/ConsolePanel.hpp"


void ConsolePanel::Render()
{
    IWindowPanel::Render();

    if (p_isOpen)
    {
        ImGui::Begin(p_windowIdentifier.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, 0xff323432);

        const std::vector<Debug::Logger::LogEntry>& logBuffer = Debug::Logger::GetInstance().GetLogBuffer();

        if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar))
        {
            for (const Debug::Logger::LogEntry& line : logBuffer)
            {
                ImVec4 color = GetColorForLogLevel(line.level);
                ImGui::TextColored(color, "%s", line.message.c_str());
            }
        }
        ImGui::EndChild();

        ImGui::PopStyleColor();
        ImGui::End();
    }
}

ImVec4 ConsolePanel::GetColorForLogLevel(const Debug::LogLevel a_level)
{
    switch (a_level)
    {
        case Debug::LogLevel::VERBOSE:  return ImVec4(0.5f, 0.5f, 0.5f, 1.0f); // gray
        case Debug::LogLevel::INFO:     return ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // green
        case Debug::LogLevel::WARNING:  return ImVec4(1.0f, 1.0f, 0.0f, 1.0f); // yellow
        case Debug::LogLevel::ERROR:    return ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // red
        case Debug::LogLevel::CRITICAL: return ImVec4(1.0f, 0.0f, 1.0f, 1.0f); // purple
        default:                 return ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // white
    }
}
