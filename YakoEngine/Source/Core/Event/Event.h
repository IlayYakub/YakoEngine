#pragma once

#include <string>

namespace YakoEngine
{

enum class EventType
{
    NONE = 0,
    // Window events
    WINDOW_CLOSE,
    WINDOW_FRAMEBUFFER_RESIZE,
    WINDOW_MOVE,
    // Keyboard events
    KEY_PRESSED,
    KEY_RELEASED,
    KEY_TYPED,
    // Mouse events
    MOUSE_BUTTON_PRESSED,
    MOUSE_BUTTON_RELEASED,
    MOUSE_MOVED,
    MOUSE_SCROLLED
};

class Event
{
public:
    explicit Event(EventType type)
        : m_type(type)
    {
    }
    virtual ~Event() = default;

    [[nodiscard]] EventType GetEventType() const { return m_type; }
    [[nodiscard]] bool      IsHandled() const { return m_handled; }
    void                    SetHandled(bool value) { m_handled = value; }

    [[nodiscard]] virtual std::string ToString() const = 0;

protected:
    EventType m_type{EventType::NONE};
    bool      m_handled{false};
};

}  // namespace YakoEngine