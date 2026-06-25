#include <gtest/gtest.h>
#include <YakoEngine.h>

using namespace YakoEngine;

namespace WindowTesting
{

TEST(WindowIdTest, ComprehensiveOperations)
{
    // Creation and cast
    WindowId id{5};
    EXPECT_EQ(static_cast<unsigned int>(id), 5);

    // Comparison
    WindowId id2{5}, id3{6};
    EXPECT_EQ(id, id2);
    EXPECT_LT(id, id3);

    // Increments
    EXPECT_EQ(static_cast<unsigned int>(id++), 5);
    EXPECT_EQ(static_cast<unsigned int>(id), 6);
    EXPECT_EQ(static_cast<unsigned int>(++id), 7);
}

// Window manager
class WindowManagerTest : public ::testing::Test
{
protected:
    void SetUp() override { manager = std::make_unique<YakoEngine::GLFWwindowWrapperManager>(); }
    void TearDown() override { manager.reset(); }
    std::unique_ptr<GLFWwindowWrapperManager> manager;
};

TEST_F(WindowManagerTest, CompleteLifecycle)
{
    // Window create
    WindowSettings settings{"LifecycleTest", 0, 0, 800, 600};
    auto           result = manager->CreateWindow(settings);
    EXPECT_TRUE(result.has_value());

    WindowId id     = result.value();
    auto     window = manager->GetWindowById(id);

    // Check state
    EXPECT_TRUE(window != nullptr);
    EXPECT_EQ(window->GetId(), id);
    EXPECT_TRUE(window->IsValid());
    EXPECT_NE(window->GetNativeHandle(), nullptr);
    EXPECT_FALSE(manager->AreAllWindowsClosed());
    EXPECT_FALSE(window->ShouldClose());

    // Close and clean
    window->Close();
    EXPECT_TRUE(window->ShouldClose());

    manager->OnUpdate();

    EXPECT_TRUE(manager->AreAllWindowsClosed());
    EXPECT_EQ(manager->GetWindowById(id), nullptr);
}

}  // namespace WindowTesting