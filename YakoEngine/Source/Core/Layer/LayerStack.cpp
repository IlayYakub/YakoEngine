#include "Core/Layer/LayerStack.h"
#include "Core/Log/Log.h"

#include <algorithm>

namespace YakoEngine
{

LayerStack::~LayerStack()
{
    for (auto& layer : m_layers)
    {
        if (layer)
            layer->OnDetach();
    }
    m_layers.clear();
}

void LayerStack::PushLayer(std::unique_ptr<Layer> layer)
{
    if (!layer)
        return;

    layer->OnAttach();

    m_layers.emplace(m_layers.begin() + static_cast<long long>(m_layerInsertIndex), std::move(layer));

    ++m_layerInsertIndex;
}

void LayerStack::PushOverlay(std::unique_ptr<Layer> overlay)
{
    if (!overlay)
        return;

    overlay->OnAttach();
    m_layers.emplace_back(std::move(overlay));
}

void LayerStack::PopLayer(const std::string& layerName)
{
    auto it = std::find_if(
        m_layers.begin(), m_layers.end(), [layerName](const auto& pLayer) { return pLayer->GetName() == layerName; }
    );

    if (it != m_layers.end())
    {
        (*it)->OnDetach();
        m_layers.erase(it);
        if (m_layerInsertIndex > 0)
            --m_layerInsertIndex;
        else
            YAKO_ERROR(LayerStack, "Layer insert index < 0!");
    }
}

void LayerStack::PopOverlay(const std::string& overlayName)
{
    auto it = std::find_if(
        m_layers.begin() + static_cast<long long>(m_layerInsertIndex),
        m_layers.end(),
        [overlayName](const auto& pOverlay) { return pOverlay->GetName() == overlayName; }
    );

    if (it != m_layers.end())
    {
        (*it)->OnDetach();
        m_layers.erase(it);
    }
}

}  // namespace YakoEngine