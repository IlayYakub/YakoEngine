#pragma once

#include "Core/Event/Event.h"

#include <sstream>

namespace YakoEngine
{

class KeyPressedEvent : public Event
{
public:
    KeyPressedEvent(int keyCode, bool repeat = false)
        : Event(EventType::KEY_PRESSED)
        , m_keyCode(keyCode)
        , m_repeat(repeat)
    {
    }

    static EventType GetStaticType() { return EventType::KEY_PRESSED; }

    [[nodiscard]] int  GetKeyCode() const { return m_keyCode; }
    [[nodiscard]] bool IsRepeat() const { return m_repeat; }

    [[nodiscard]] std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: key=" << m_keyCode;
        if (m_repeat)
            ss << " (repeat)";
        return ss.str();
    }

private:
    int  m_keyCode;
    bool m_repeat;
};

class KeyReleasedEvent : public Event
{
public:
    explicit KeyReleasedEvent(int keyCode)
        : Event(EventType::KEY_RELEASED)
        , m_keyCode(keyCode)
    {
    }

    static EventType GetStaticType() { return EventType::KEY_RELEASED; }

    [[nodiscard]] int GetKeyCode() const { return m_keyCode; }

    [[nodiscard]] std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: key=" << m_keyCode;
        return ss.str();
    }

private:
    int m_keyCode;
};

class KeyTypedEvent : public Event
{
public:
    explicit KeyTypedEvent(int keyCode)
        : Event(EventType::KEY_TYPED)
        , m_keyCode(keyCode)
    {
    }

    static EventType GetStaticType() { return EventType::KEY_TYPED; }

    [[nodiscard]] int GetKeyCode() const { return m_keyCode; }

    [[nodiscard]] std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyTypedEvent: key=" << m_keyCode;
        return ss.str();
    }

private:
    int m_keyCode;
};

}  // namespace YakoEngine