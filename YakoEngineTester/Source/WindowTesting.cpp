#include <gtest/gtest.h>
#include <YakoEngine.h>

using namespace YakoEngine;

namespace WindowTesting
{

TEST(WindowIdTest, Core)
{
    // Creation and cast
    WindowId baseId{5};
    EXPECT_EQ(static_cast<unsigned int>(baseId), 5);

    // Comparison
    WindowId equivalentId{5};
    WindowId greaterId{6};

    EXPECT_EQ(baseId, equivalentId);
    EXPECT_LT(baseId, greaterId);

    // Increments
    EXPECT_EQ(static_cast<unsigned int>(baseId++), 5);
    EXPECT_EQ(static_cast<unsigned int>(baseId), 6);
    EXPECT_EQ(static_cast<unsigned int>(++baseId), 7);
}

// Window manager fixture
class WindowManagerTest : public ::testing::Test
{
protected:
    void SetUp() override { windowManager = std::make_unique<YakoEngine::GLFWwindowWrapperManager>(); }

    void TearDown() override { windowManager.reset(); }

    std::unique_ptr<GLFWwindowWrapperManager> windowManager;
};

TEST_F(WindowManagerTest, CompleteLifecycleValidation)
{
    // Window create
    WindowSettings testWindowSettings{"LifecycleTest", 0, 0, 800, 600};
    auto           windowCreationResult = windowManager->CreateWindow(testWindowSettings);

    EXPECT_TRUE(windowCreationResult.has_value());

    WindowId activeWindowId = windowCreationResult.value();
    auto     createdWindow  = windowManager->GetWindowById(activeWindowId).value();

    // Check state
    EXPECT_NE(createdWindow, nullptr);
    EXPECT_EQ(createdWindow->GetId(), activeWindowId);
    EXPECT_TRUE(createdWindow->IsValid());
    EXPECT_NE(createdWindow->GetNativeHandle(), nullptr);

    EXPECT_FALSE(windowManager->AreAllWindowsClosed());
    EXPECT_FALSE(createdWindow->ShouldClose());

    // Close and clean
    createdWindow->Close();
    EXPECT_TRUE(createdWindow->ShouldClose());

    windowManager->OnUpdate();

    EXPECT_TRUE(windowManager->AreAllWindowsClosed());
    EXPECT_EQ(windowManager->GetWindowById(activeWindowId).error(), YakoEngine::WindowManagerErrors::WINDOW_NOT_FOUND);
}

}  // namespace WindowTesting