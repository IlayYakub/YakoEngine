#include <gtest/gtest.h>
#include <YakoEngine.h>

using namespace YakoEngine;

namespace EventsTesting
{

TEST(EventsTest, Core)
{
    // Keyboard events
    KeyPressedEvent keyEvent(42, true);
    EXPECT_EQ(keyEvent.GetEventType(), EventType::KEY_PRESSED);
    EXPECT_EQ(keyEvent.GetStaticType(), EventType::KEY_PRESSED);
    EXPECT_EQ(keyEvent.GetKeyCode(), 42);
    EXPECT_TRUE(keyEvent.IsRepeat());
    EXPECT_NE(keyEvent.ToString().find("42"), std::string::npos);

    // Mouse events
    MouseMovedEvent mouseEvent(10.5, 20.0);
    EXPECT_EQ(mouseEvent.GetEventType(), EventType::MOUSE_MOVED);
    EXPECT_DOUBLE_EQ(mouseEvent.GetX(), 10.5);
    EXPECT_DOUBLE_EQ(mouseEvent.GetY(), 20.0);
    EXPECT_FALSE(mouseEvent.IsHandled());

    // Window Events
    WindowFramebufferResizeEvent resizeEvent(800, 600);
    EXPECT_EQ(resizeEvent.GetEventType(), EventType::WINDOW_FRAMEBUFFER_RESIZE);
    EXPECT_EQ(resizeEvent.GetWidth(), 800);
    EXPECT_EQ(resizeEvent.GetHeight(), 600);

    // Handled
    EXPECT_FALSE(keyEvent.IsHandled());
    keyEvent.SetHandled(true);
    EXPECT_TRUE(keyEvent.IsHandled());
}

}  // namespace EventsTesting