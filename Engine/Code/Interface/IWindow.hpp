#pragma once

#include <string>
#include <GLFW/glfw3.h>

#include "Logger.hpp"
#include "Vector2.hpp"

class GLFWWindow;

class IWindow
{
public:
    virtual ~IWindow() = default;

    virtual GLFWwindow* Initialize(const std::string& a_name, const bool& a_fullscreen, const int& a_width = 800, const int& a_height = 600) = 0;
    virtual void Update() const = 0;
    virtual void PollEvents() const = 0;
    virtual void Destroy() const = 0;
    virtual void SetSize(const Maths::Vector2& a_size) = 0;
    virtual void SetOpacity(const float& a_alpha) = 0;
    virtual void SetTitle(const std::string& a_name) = 0;
    virtual void ProcessEvents() = 0;

    [[nodiscard]] virtual float GetOpacity() const = 0;
    [[nodiscard]] virtual bool ShouldClose() const = 0;
    [[nodiscard]] virtual std::string GetTitle() const = 0;
    [[nodiscard]] virtual Maths::Vector2 GetSize() const = 0;

    virtual void GetFrameBufferSize(int* a_width, int* a_height) = 0;

    virtual GLFWWindow* CastGLFW()
    {
        DEBUG_LOG_INFO("Wrong Cast\n");
        return nullptr;
    }
};
