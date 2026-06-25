#include "Engine.h"
#include "Core/Log/Log.h"

namespace YakoEngine
{

Engine::Engine(const EngineSettings& settings)
    : m_settings(settings)
{
    if (auto log_res = Log::CreateInstance(); log_res.has_value())
    {
        YAKO_INFO(Log, "Log created successfully!");
    }
}

Engine::~Engine()
{
}

void Engine::Run()
{
    while (true)
    {
    }
}

const EngineSettings& Engine::GetSettings() const
{
    return m_settings;
}

}  // namespace YakoEngine