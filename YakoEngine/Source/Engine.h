#pragma once

namespace YakoEngine
{

struct EngineSettings
{
};

class Engine final
{
public:
    explicit Engine(const EngineSettings& settings);
    virtual ~Engine();

    void Run();

    const EngineSettings& GetSettings() const;

private:
    EngineSettings m_settings;
};

}  // namespace YakoEngine