#pragma once

#include "Core/Event/Event.h"

#include <string>

namespace YakoEngine
{

class Layer
{
public:
    explicit Layer(std::string name = "Layer");
    virtual ~Layer() = default;

    [[nodiscard]] bool IsActive() const { return m_isActive; }
    void               SetActive(bool value) { m_isActive = value; }

    virtual void OnAttach()            = 0;
    virtual void OnDetach()            = 0;
    virtual void OnUpdate()            = 0;
    virtual void OnEvent(Event& event) = 0;

    [[nodiscard]] const std::string& GetName() const { return m_name; }

protected:
    std::string m_name;
    bool        m_isActive{true};
};

}  // namespace YakoEngine