#pragma once

#include "Platform/Window/IWindowManager.h"
#include "Core/Layer/Layer.h"
#include "Core/Layer/LayerStack.h"
#include "Core/Event/Event.h"

#include <memory>
#include <expected>

namespace YakoEngine
{

using EngineCallback = std::function<void(Event& event)>;

struct EngineSettings
{
};

class Engine final
{
public:
    explicit Engine(const EngineSettings& settings);
    ~Engine();

    [[nodiscard]] const EngineSettings& GetSettings() const;

    // Reaction
    void OnEvent(Event& event);

    // Layer management
    void PushLayer(std::unique_ptr<Layer> layer);
    void PushOverlay(std::unique_ptr<Layer> overlay);
    void PopLayer(const std::string& layerName);
    void PopOverlay(const std::string& overlayName);

    // Window management
    [[nodiscard]] std::expected<WindowId, WindowManagerErrors> CreateWindow(const WindowSettings& settings);
    [[nodiscard]] std::expected<std::shared_ptr<IWindow>, WindowManagerErrors> GetWindowById(const WindowId& id);

    // Lifecycle
    void Run();

private:
    EngineCallback                  m_engineCallback;
    EngineSettings                  m_settings{};
    std::unique_ptr<IWindowManager> m_windowManager{nullptr};
    std::unique_ptr<LayerStack>     m_layerStack{nullptr};
};

}  // namespace YakoEngine