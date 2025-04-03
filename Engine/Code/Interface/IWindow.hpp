#pragma once

#include <string>

#include "Logger.hpp"
#include "Vector2.hpp"

class GLFWWindow;


class IWindow
{
public:
    virtual ~IWindow() = default;

    virtual void Initialize(const std::string& a_name, const int& a_width, const int& a_height) = 0;
    virtual void Update() const = 0;
    virtual void PollEvents() const = 0;
    [[nodiscard]] virtual bool ShouldClose() const = 0;
    virtual void Destroy() const = 0;

    virtual void SetSize(const Maths::Vector2& a_size) = 0;
    virtual void SetOpacity(const float& a_alpha) = 0;
    virtual void SetTitle(const std::string& a_name) = 0;

    virtual Maths::Vector2 GetSize() const = 0;
    virtual float GetOpacity() const = 0;
    [[nodiscard]] virtual std::string GetTitle() const = 0;


    virtual GLFWWindow* CastGLFW()
    {
        DEBUG_LOG_INFO("Wrong Cast\n");
        return nullptr;
    }
};
