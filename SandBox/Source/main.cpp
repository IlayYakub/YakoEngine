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
        onSomeEvent.Broadcast(event);
        event.SetHandled(true);
    }

    DECLARE_PROTECTED_MULTICAST_DELEGATE(GameplayLayer, onSomeEvent, YakoEngine::Event&);
};

int main()
{
    YakoEngine::EngineSettings settings;
    YakoEngine::Engine         engine(settings);

    auto gameplayLayer = std::make_unique<GameplayLayer>("GameplayLayer");

    auto subscriberResult =
        gameplayLayer->onSomeEvent.AddSubscriber([](YakoEngine::Event& event)
                                                 { YAKO_INFO(GameplayLayer, "Delegate: {}", event.ToString()); });

    if (!subscriberResult)
    {
        switch (subscriberResult.error())
        {
            case YakoEngine::DelegateErrors::EmptySubscriber:
                YAKO_ERROR(GameplayLayer, "Failed to subscribe: subscriber is empty.");
                break;

            case YakoEngine::DelegateErrors::SubscriptionFailed:
                YAKO_ERROR(GameplayLayer, "Failed to subscribe.");
                break;
        }

        return EXIT_FAILURE;
    }

    const YakoEngine::SubscriberId subscriberId = subscriberResult.value();

    engine.PushLayer(std::move(gameplayLayer));
    engine.PushLayer(std::make_unique<MenuLayer>("MenuLayer"));

    YakoEngine::WindowSettings windowSettings{};
    auto                       windowCreationResult = engine.CreateWindow(windowSettings);

    if (windowCreationResult.has_value())
    {
        engine.Run();
    }

    return EXIT_SUCCESS;
}