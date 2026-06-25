#pragma once

#include "Platform/Window/IWindowManager.h"

#include <memory>
#include <expected>

namespace YakoEngine
{

struct EngineSettings
{
};

class Engine final
{
public:
    explicit Engine(const EngineSettings& settings);
    ~Engine();

    [[nodiscard]] const EngineSettings& GetSettings() const;

    // Window management
    [[nodiscard]] std::expected<WindowId, WindowManagerErrors> CreateWindow(const WindowSettings& settings);
    [[nodiscard]] std::expected<std::shared_ptr<IWindow>, WindowManagerErrors> GetWindowById(const WindowId& id);
    void                                                                       CloseWindow(const WindowId& id);

    // Lifecycle
    void Run();

private:
    EngineSettings                  m_settings;
    std::unique_ptr<IWindowManager> m_windowManager{nullptr};
};

}  // namespace YakoEngine