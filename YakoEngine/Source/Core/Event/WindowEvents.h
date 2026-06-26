#pragma once

#include "Core/Event/Event.h"

#include <sstream>

namespace YakoEngine
{

class WindowCloseEvent : public Event
{
public:
    WindowCloseEvent()
        : Event(EventType::WINDOW_CLOSE)
    {
    }

    static EventType GetStaticType() { return EventType::WINDOW_CLOSE; }

    [[nodiscard]] std::string ToString() const override { return "WindowCloseEvent"; }
};

class WindowFramebufferResizeEvent : public Event
{
public:
    WindowFramebufferResizeEvent(int width, int height)
        : Event(EventType::WINDOW_FRAMEBUFFER_RESIZE)
        , m_width(width)
        , m_height(height)
    {
    }

    static EventType GetStaticType() { return EventType::WINDOW_FRAMEBUFFER_RESIZE; }

    [[nodiscard]] int GetWidth() const { return m_width; }
    [[nodiscard]] int GetHeight() const { return m_height; }

    [[nodiscard]] std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowFramebufferResizeEvent: " << m_width << "x" << m_height;
        return ss.str();
    }

private:
    int m_width;
    int m_height;
};

class WindowMoveEvent : public Event
{
public:
    WindowMoveEvent(int x, int y)
        : Event(EventType::WINDOW_MOVE)
        , m_x(x)
        , m_y(y)
    {
    }

    static EventType GetStaticType() { return EventType::WINDOW_MOVE; }

    [[nodiscard]] int GetX() const { return m_x; }
    [[nodiscard]] int GetY() const { return m_y; }

    [[nodiscard]] std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowMoveEvent: x=" << m_x << ", y=" << m_y;
        return ss.str();
    }

private:
    int m_x;
    int m_y;
};

}  // namespace YakoEngine