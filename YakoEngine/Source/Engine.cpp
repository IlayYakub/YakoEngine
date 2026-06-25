#include "Engine.h"
#include "Core/Log/Log.h"
#include "Platform/Window/GLFW/GLFWwindowWrapperManager.h"

namespace YakoEngine
{

Engine::Engine(const EngineSettings& settings)
    : m_settings(settings)
{
    if (auto log_res = Log::CreateInstance(); log_res.has_value())
    {
        YAKO_INFO(Engine, "Log subsystem initialized successfully.");
    }

    m_windowManager = std::make_unique<GLFWwindowWrapperManager>();
    if (m_windowManager)
    {
        YAKO_INFO(Engine, "Window manager subsystem initialized successfully.");
    }
}

Engine::~Engine()
{
    YAKO_INFO(Engine, "Engine shutting down...");
}

std::expected<WindowId, WindowManagerErrors> Engine::CreateWindow(const WindowSettings& settings)
{
    if (!m_windowManager)
    {
        YAKO_ERROR(Engine, "Cannot create window '{}', WindowManager is null!", settings.m_title);
        return std::unexpected(WindowManagerErrors::NOT_INITIALIZED);
    }

    return m_windowManager->CreateWindow(settings);
}

std::expected<std::shared_ptr<IWindow>, WindowManagerErrors> Engine::GetWindowById(const WindowId& id)
{
    if (!m_windowManager)
    {
        YAKO_ERROR(Engine, "Cannot get window with ID {}, WindowManager is null!", static_cast<unsigned int>(id));
        return std::unexpected(WindowManagerErrors::NOT_INITIALIZED);
    }

    return m_windowManager->GetWindowById(id);
}

void Engine::CloseWindow(const WindowId& id)
{
    if (!m_windowManager)
        return;

    if (auto window = m_windowManager->GetWindowById(id); window)
    {
        window->Close();
    }
    else
    {
        YAKO_ERROR(Engine, "Failed to close window: Window with ID {} does not exist!", static_cast<unsigned int>(id));
    }
}

void Engine::Run()
{
    YAKO_INFO(Engine, "Engine main loop started.");

    while (m_windowManager && !m_windowManager->AreAllWindowsClosed())
    {
        m_windowManager->OnUpdate();
    }

    YAKO_INFO(Engine, "Engine main loop stopped because all windows were closed.");
}

const EngineSettings& Engine::GetSettings() const
{
    return m_settings;
}

}  // namespace YakoEngine