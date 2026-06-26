#include "Engine.h"
#include "Core/Log/Log.h"
#include "Platform/Window/GLFW/GLFWwindowWrapperManager.h"

namespace YakoEngine
{

Engine::Engine(const EngineSettings& settings)
    : m_settings(settings)
{
    // Engine callback
    m_engineCallback = [this](Event& event) { OnEvent(event); };

    // Log
    const auto& logCreationResult = Log::CreateInstance();
    if (!logCreationResult.has_value())
    {
        YAKO_WARN(Engine, "Log subsystem was already initialized successfully.");
    }
    else
    {
        YAKO_INFO(Engine, "Log subsystem initialized successfully.");
    }

    // Window manager
    m_windowManager = std::make_unique<GLFWwindowWrapperManager>();
    YAKO_INFO(Engine, "Window manager subsystem initialized successfully.");

    // Layer stack
    m_layerStack = std::make_unique<LayerStack>();
    YAKO_INFO(Engine, "Layer subsystem initialized successfully.");
}

Engine::~Engine()
{
    YAKO_INFO(Engine, "Engine shutting down...");
}

const EngineSettings& Engine::GetSettings() const
{
    return m_settings;
}

void Engine::OnEvent(Event& event)
{
    if (!m_layerStack)
        return;

    for (auto itLayer = m_layerStack->rbegin(); itLayer != m_layerStack->rend(); ++itLayer)
    {
        const auto& layer = *(itLayer);
        if (layer->IsActive() && !event.IsHandled())
        {
            layer->OnEvent(event);
        }
    }
}

void Engine::PushLayer(std::unique_ptr<Layer> layer)
{
    if (!m_layerStack || !layer)
    {
        YAKO_ERROR(Engine, "LayerStack or Layer is nullptr!");
        return;
    }
    else
    {
        m_layerStack->PushLayer(std::move(layer));
    }
}

void Engine::PushOverlay(std::unique_ptr<Layer> overlay)
{
    if (!m_layerStack || !overlay)
    {
        YAKO_ERROR(Engine, "LayerStack or Overlay is nullptr!");
        return;
    }
    else
    {
        m_layerStack->PushOverlay(std::move(overlay));
    }
}

void Engine::PopLayer(const std::string& layerName)
{
    if (!m_layerStack)
    {
        YAKO_ERROR(Engine, "LayerStack is nullptr!");
        return;
    }
    else
    {
        m_layerStack->PopLayer(layerName);
    }
}

void Engine::PopOverlay(const std::string& overlayName)
{
    if (!m_layerStack)
    {
        YAKO_ERROR(Engine, "LayerStack is nullptr!");
        return;
    }
    else
    {
        m_layerStack->PopOverlay(overlayName);
    }
}

std::expected<WindowId, WindowManagerErrors> Engine::CreateWindow(const WindowSettings& settings)
{
    if (!m_windowManager)
    {
        YAKO_ERROR(Engine, "Cannot create window '{}', WindowManager is null!", settings.m_title);
        return std::unexpected(WindowManagerErrors::NOT_INITIALIZED);
    }

    const auto windowCreationResult = m_windowManager->CreateWindow(settings);
    if (!windowCreationResult)
    {
        YAKO_ERROR(Engine, "Didn't create window!");
        return std::unexpected(windowCreationResult.error());
    }

    const auto windowSearchResult = m_windowManager->GetWindowById(windowCreationResult.value());
    if (!windowSearchResult)
    {
        YAKO_ERROR(Engine, "Window created but not found!");
        return std::unexpected(windowSearchResult.error());
    }

    auto& window = windowSearchResult.value();
    window->SetEngineCallback(m_engineCallback);

    return windowCreationResult;
}

std::expected<std::shared_ptr<IWindow>, WindowManagerErrors> Engine::GetWindowById(const WindowId& id)
{
    if (!m_windowManager)
    {
        YAKO_ERROR(Engine, "Cannot get window with ID {}, WindowManager is null!", static_cast<unsigned int>(id));
        return std::unexpected(WindowManagerErrors::NOT_INITIALIZED);
    }

    const auto window = m_windowManager->GetWindowById(id);
    if (!window.has_value())
    {
        YAKO_ERROR(Engine, "Window not found!");
        return std::unexpected(WindowManagerErrors::WINDOW_NOT_FOUND);
    }

    return window;
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

}  // namespace YakoEngine