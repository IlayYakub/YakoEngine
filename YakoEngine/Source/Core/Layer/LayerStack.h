#pragma once

#include "Core/Layer/Layer.h"

#include <memory>
#include <vector>

namespace YakoEngine
{

class LayerStack final
{
public:
    explicit LayerStack() = default;
    ~LayerStack();

    void PushLayer(std::unique_ptr<Layer> layer);
    void PushOverlay(std::unique_ptr<Layer> overlay);
    void PopLayer(const std::string& layerName);
    void PopOverlay(const std::string& overlayName);

    [[nodiscard]] auto begin() { return m_layers.begin(); }
    [[nodiscard]] auto end() { return m_layers.end(); }
    [[nodiscard]] auto begin() const { return m_layers.begin(); }
    [[nodiscard]] auto end() const { return m_layers.end(); }
    [[nodiscard]] auto rbegin() { return m_layers.rbegin(); }
    [[nodiscard]] auto rend() { return m_layers.rend(); }
    [[nodiscard]] auto rbegin() const { return m_layers.rbegin(); }
    [[nodiscard]] auto rend() const { return m_layers.rend(); }

private:
    std::vector<std::unique_ptr<Layer>> m_layers;
    std::size_t                         m_layerInsertIndex = 0;
};

}  // namespace YakoEngine