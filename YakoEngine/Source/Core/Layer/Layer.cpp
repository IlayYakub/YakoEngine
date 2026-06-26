#include "Core/Layer/Layer.h"

namespace YakoEngine
{

Layer::Layer(std::string name)
    : m_name(std::move(name))
{
}

}  // namespace YakoEngine