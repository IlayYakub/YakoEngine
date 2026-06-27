#include <gtest/gtest.h>
#include <YakoEngine.h>

using namespace YakoEngine;

namespace DelegateTest
{

// Delegate core
class TestDelegateOwner
{
public:
    DECLARE_PROTECTED_MULTICAST_DELEGATE(TestDelegateOwner, onTestEvent, int);

    void Trigger(int value) { onTestEvent.Broadcast(value); }
};

TEST(DelegateTest, BasicFunctionality)
{
    TestDelegateOwner owner;

    int callCount         = 0;
    int lastReceivedValue = 0;

    // Subscribe
    auto sub1Result = owner.onTestEvent.AddSubscriber(
        [&](int val)
        {
            callCount++;
            lastReceivedValue = val;
        }
    );
    EXPECT_TRUE(sub1Result.has_value()) << "First subscription failed!";

    // Broadcast
    owner.Trigger(42);
    EXPECT_EQ(callCount, 1);
    EXPECT_EQ(lastReceivedValue, 42);

    // Another subscriber
    auto sub2Result = owner.onTestEvent.AddSubscriber([&](int val) { callCount += 10; });
    EXPECT_TRUE(sub2Result.has_value());

    owner.Trigger(5);

    EXPECT_EQ(callCount, 12);
    EXPECT_EQ(lastReceivedValue, 5);

    // Empty subscriber
    std::function<void(int)> emptySubscriber;
    auto                     failResult = owner.onTestEvent.AddSubscriber(emptySubscriber);

    EXPECT_FALSE(failResult.has_value());
    EXPECT_EQ(failResult.error(), DelegateErrors::EmptySubscriber);

    // Unsubscribe
    owner.onTestEvent.RemoveSubscriber(sub1Result.value());

    owner.Trigger(100);
    EXPECT_EQ(callCount, 22);
}

// Simple game simulation
struct ShootData
{
    float x;
    float y;
    int   damage;
};

class Player
{
public:
    DECLARE_PROTECTED_MULTICAST_DELEGATE(Player, onShoot, const ShootData&);

    void Shoot(float x, float y, int damage)
    {
        ShootData data{x, y, damage};
        onShoot.Broadcast(data);
    }
};

class GameplayLayer final : public YakoEngine::Layer
{
public:
    GameplayLayer(const std::string& name, Player& player, bool& outAudioPlayed, bool& outParticlesAppeared)
        : YakoEngine::Layer(name)
    {
        // Subscriber 1: Audio system
        auto addResult1 =
            player.onShoot.AddSubscriber([&outAudioPlayed](const ShootData& data) { outAudioPlayed = true; });

        // Subscriber 2: Particle system
        auto addResult2 = player.onShoot.AddSubscriber([&outParticlesAppeared](const ShootData& data)
                                                       { outParticlesAppeared = true; });
    }

    // Обязательная реализация интерфейса YakoEngine::Layer
    void OnAttach() override {}
    void OnDetach() override {}
    void OnUpdate() override {}
    void OnEvent(YakoEngine::Event& event) override {}
};

TEST(DelegateTest, GameplaySimulation)
{
    EngineSettings settings;
    Engine         engine(settings);
    Player         player;

    bool audioPlayed       = false;
    bool particlesAppeared = false;

    auto gameplayLayer = std::make_unique<GameplayLayer>("GameplayLayer", player, audioPlayed, particlesAppeared);

    EXPECT_FALSE(audioPlayed);
    EXPECT_FALSE(particlesAppeared);

    engine.PushLayer(std::move(gameplayLayer));

    player.Shoot(15.5f, 30.0f, 50);

    EXPECT_TRUE(audioPlayed) << "Audio subscriber did not trigger!";
    EXPECT_TRUE(particlesAppeared) << "Particles subscriber did not trigger!";
}

}  // namespace DelegateTest