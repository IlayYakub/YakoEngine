#pragma once

#include "Platform/Window/IWindow.h"

#include <expected>
#include <memory>

namespace YakoEngine
{

enum class WindowManagerErrors
{
    NOT_INITIALIZED,
    CANT_CREATE_WINDOW,
    WINDOW_NOT_FOUND
};

class IWindowManager
{
public:
    explicit IWindowManager() = default;
    virtual ~IWindowManager() = default;

    [[nodiscard]] virtual std::expected<WindowId, WindowManagerErrors> CreateWindow(const WindowSettings& settings) = 0;
    [[nodiscard]] virtual std::expected<std::shared_ptr<IWindow>, WindowManagerErrors> GetWindowById(
        const WindowId& id
    )                                                      = 0;
    [[nodiscard]] virtual bool AreAllWindowsClosed() const = 0;
    virtual void               OnUpdate()                  = 0;

protected:
    EngineCallback m_engineCallback;
    bool           m_initialized{false};
    WindowId       m_nextWindowId{0};
};

}  // namespace YakoEngine