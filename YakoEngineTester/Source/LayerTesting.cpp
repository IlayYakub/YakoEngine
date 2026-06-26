#include <gtest/gtest.h>
#include <YakoEngine.h>
#include <memory>

using namespace YakoEngine;
namespace LayersTesting
{

class MockLayer : public Layer
{
public:
    MockLayer(const std::string& name)
        : Layer(name)
    {
    }
    void OnAttach() override {}
    void OnDetach() override {}
    void OnUpdate() override {}
    void OnEvent(Event& event) override { YAKO_INFO(MockLayer, "{}: {}", m_name, event.ToString()); }
};

TEST(LayerStackTest, Core)
{
    LayerStack stack;

    // Create layers
    auto layer   = std::make_unique<MockLayer>("GameLayer");
    auto overlay = std::make_unique<MockLayer>("UIOverlay");

    EXPECT_EQ(layer->GetName(), "GameLayer");
    EXPECT_TRUE(layer->IsActive());
    layer->SetActive(false);
    EXPECT_FALSE(layer->IsActive());
    layer->SetActive(true);

    // Push
    stack.PushLayer(std::make_unique<MockLayer>("GameLayer"));
    stack.PushOverlay(std::make_unique<MockLayer>("UIOverlay"));

    // Order
    int count = 0;
    for (auto it = stack.begin(); it != stack.end(); ++it)
    {
        if (count == 0)
            EXPECT_EQ((*it)->GetName(), "GameLayer");
        if (count == 1)
            EXPECT_EQ((*it)->GetName(), "UIOverlay");
        count++;
    }
    EXPECT_EQ(count, 2);

    // Simulating Engine::OnEvent(Event& event)
    WindowCloseEvent testEvent1;
    for (auto it = stack.rbegin(); it != stack.rend(); ++it)
    {
        if ((*it)->IsActive() && !testEvent1.IsHandled())
        {
            (*it)->OnEvent(testEvent1);
        }
    }

    // Pop
    stack.PopLayer("GameLayer");
    stack.PopOverlay("UIOverlay");

    // Check empty
    int remainingCount = 0;
    for (auto it = stack.begin(); it != stack.end(); ++it)
    {
        remainingCount++;
    }
    EXPECT_EQ(remainingCount, 0);
}

}  // namespace LayersTesting