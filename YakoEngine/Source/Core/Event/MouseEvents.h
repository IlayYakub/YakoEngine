#pragma once

#include "Core/Event/Event.h"

#include <sstream>

namespace YakoEngine
{

class MouseButtonPressedEvent : public Event
{
public:
    explicit MouseButtonPressedEvent(int button)
        : Event(EventType::MOUSE_BUTTON_PRESSED)
        , m_button(button)
    {
    }

    static EventType GetStaticType() { return EventType::MOUSE_BUTTON_PRESSED; }

    [[nodiscard]] int GetButton() const { return m_button; }

    [[nodiscard]] std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: button=" << m_button;
        return ss.str();
    }

private:
    int m_button;
};

class MouseButtonReleasedEvent : public Event
{
public:
    explicit MouseButtonReleasedEvent(int button)
        : Event(EventType::MOUSE_BUTTON_RELEASED)
        , m_button(button)
    {
    }

    static EventType GetStaticType() { return EventType::MOUSE_BUTTON_RELEASED; }

    [[nodiscard]] int GetButton() const { return m_button; }

    [[nodiscard]] std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: button=" << m_button;
        return ss.str();
    }

private:
    int m_button;
};

class MouseMovedEvent : public Event
{
public:
    MouseMovedEvent(double x, double y)
        : Event(EventType::MOUSE_MOVED)
        , m_x(x)
        , m_y(y)
    {
    }

    static EventType GetStaticType() { return EventType::MOUSE_MOVED; }

    [[nodiscard]] double GetX() const { return m_x; }
    [[nodiscard]] double GetY() const { return m_y; }

    [[nodiscard]] std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: x=" << m_x << ", y=" << m_y;
        return ss.str();
    }

private:
    double m_x;
    double m_y;
};

class MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent(double xOffset, double yOffset)
        : Event(EventType::MOUSE_SCROLLED)
        , m_xOffset(xOffset)
        , m_yOffset(yOffset)
    {
    }

    static EventType GetStaticType() { return EventType::MOUSE_SCROLLED; }

    [[nodiscard]] double GetXOffset() const { return m_xOffset; }
    [[nodiscard]] double GetYOffset() const { return m_yOffset; }

    [[nodiscard]] std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseScrolledEvent: xOffset=" << m_xOffset << ", yOffset=" << m_yOffset;
        return ss.str();
    }

private:
    double m_xOffset;
    double m_yOffset;
};

}  // namespace YakoEngine