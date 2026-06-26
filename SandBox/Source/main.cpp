#include <YakoEngine.h>

class MenuLayer final : public YakoEngine::Layer
{
public:
    explicit MenuLayer(const std::string& layerName)
        : YakoEngine::Layer(layerName)
    {
    }

    void OnAttach() override {}
    void OnDetach() override {}
    void OnUpdate() override {}
    void OnEvent(YakoEngine::Event& event) override
    {
        USER_INFO(MenuLayer, "{}", event.ToString());
        event.SetHandled(false);
    }
};

class GameplayLayer final : public YakoEngine::Layer
{
public:
    explicit GameplayLayer(const std::string& layerName)
        : YakoEngine::Layer(layerName)
    {
    }

    void OnAttach() override {}
    void OnDetach() override {}
    void OnUpdate() override {}
    void OnEvent(YakoEngine::Event& event) override
    {
        USER_INFO(GameplayLayer, "{}", event.ToString());
        event.SetHandled(true);
    }
};

int main()
{
    // Engine setup
    YakoEngine::EngineSettings settings;
    YakoEngine::Engine         engine(settings);

    // Layer setup
    engine.PushLayer(std::make_unique<GameplayLayer>("GameplayLayer"));
    engine.PushLayer(std::make_unique<MenuLayer>("MenuLayer"));

    // Main window
    YakoEngine::WindowSettings windowSettings{};
    auto                       windowCreationResult = engine.CreateWindow(windowSettings);
    if (windowCreationResult.has_value())
    {
        engine.Run();
    }

    return 0;
}