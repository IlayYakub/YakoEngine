#pragma once

#include <string>
#include <functional>

namespace YakoEngine
{

struct WindowId final
{
    explicit WindowId(unsigned int value)
        : m_id(value)
    {
    }
    ~WindowId() = default;

    explicit operator unsigned int() const { return m_id; }

    auto operator<=>(const WindowId&) const = default;

    WindowId& operator++()
    {
        ++m_id;
        return *this;
    }

    WindowId operator++(int)
    {
        WindowId old = *this;
        ++m_id;
        return old;
    }

    unsigned int m_id{0};
};

struct WindowSettings
{
    std::string m_title{"YakoWindow"};
    int         m_xPos{50};
    int         m_yPos{50};
    int         m_width{800};
    int         m_height{500};
};

class IWindow
{
public:
    IWindow(const WindowSettings& settings, const WindowId& id)
        : m_settings(settings)
        , m_id(id)
    {
    }
    virtual ~IWindow() = default;

    [[nodiscard]] const WindowId&       GetId() const { return m_id; }
    [[nodiscard]] const WindowSettings& GetSettings() const { return m_settings; }

    [[nodiscard]] virtual void* GetNativeHandle() const = 0;
    [[nodiscard]] virtual bool  IsValid() const         = 0;
    [[nodiscard]] virtual bool  ShouldClose() const     = 0;
    virtual void                Open()                  = 0;
    virtual void                Hide()                  = 0;
    virtual void                Close()                 = 0;

protected:
    WindowSettings m_settings{};
    WindowId       m_id{0};
};

}  // namespace YakoEngine

namespace std
{
template <>
struct hash<YakoEngine::WindowId>
{
    size_t operator()(const YakoEngine::WindowId& id) const noexcept { return std::hash<unsigned int>{}(id.m_id); }
};
}  // namespace std