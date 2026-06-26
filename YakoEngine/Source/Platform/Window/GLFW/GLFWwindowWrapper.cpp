#include "Platform/Window/GLFW/GLFWwindowWrapper.h"
#include "Core/Event/WindowEvents.h"
#include "Core/Event/KeyboardEvents.h"
#include "Core/Event/MouseEvents.h"
#include "Core/Log/Log.h"

#include <GLFW/glfw3.h>

namespace YakoEngine
{

GLFWwindowWrapper::GLFWwindowWrapper(const WindowSettings& settings, const WindowId& id)
    : IWindow(settings, id)
{
    // Window creation
    m_window = glfwCreateWindow(settings.m_width, settings.m_height, settings.m_title.c_str(), nullptr, nullptr);

    if (!m_window)
    {
        YAKO_FATAL(
            Window,
            "Failed to create GLFW window '{}' (Size: {}x{})",
            settings.m_title,
            settings.m_width,
            settings.m_height
        );
        return;
    }

    glfwSetWindowPos(m_window, settings.m_xPos, settings.m_yPos);

    // Callbacks
    glfwSetWindowUserPointer(m_window, this);

    // Window
    // Window close
    glfwSetWindowCloseCallback(
        m_window,
        [](GLFWwindow* window)
        {
            GLFWwindowWrapper* windowWrapper = static_cast<GLFWwindowWrapper*>(glfwGetWindowUserPointer(window));
            if (const auto& engineCallback = windowWrapper->GetEngineCallback(); engineCallback)
            {
                WindowCloseEvent event{};
                engineCallback(event);
            }
        }
    );

    // Window framebuffer resize
    glfwSetFramebufferSizeCallback(
        m_window,
        [](GLFWwindow* window, int width, int height)
        {
            GLFWwindowWrapper* windowWrapper = static_cast<GLFWwindowWrapper*>(glfwGetWindowUserPointer(window));
            if (const auto& engineCallback = windowWrapper->GetEngineCallback(); engineCallback)
            {
                WindowFramebufferResizeEvent event{width, height};
                engineCallback(event);
            }
        }
    );

    // Window pos
    glfwSetWindowPosCallback(
        m_window,
        [](GLFWwindow* window, int xpos, int ypos)
        {
            GLFWwindowWrapper* windowWrapper = static_cast<GLFWwindowWrapper*>(glfwGetWindowUserPointer(window));
            if (const auto& engineCallback = windowWrapper->GetEngineCallback(); engineCallback)
            {
                WindowMoveEvent event{xpos, ypos};
                engineCallback(event);
            }
        }
    );

    // Keyboard
    // Key press/release
    glfwSetKeyCallback(
        m_window,
        [](GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
        {
            GLFWwindowWrapper* windowWrapper = static_cast<GLFWwindowWrapper*>(glfwGetWindowUserPointer(window));
            if (const auto& engineCallback = windowWrapper->GetEngineCallback(); engineCallback)
            {
                switch (action)
                {
                    case GLFW_PRESS:
                    {
                        KeyPressedEvent event{key, false};
                        engineCallback(event);
                        break;
                    }

                    case GLFW_REPEAT:
                    {
                        KeyPressedEvent event{key, true};
                        engineCallback(event);
                        break;
                    }

                    case GLFW_RELEASE:
                    {
                        KeyReleasedEvent event{key};
                        engineCallback(event);
                        break;
                    }

                    default:
                        break;
                }
            }
        }
    );

    // Character input
    glfwSetCharCallback(
        m_window,
        [](GLFWwindow* window, unsigned int codepoint)
        {
            GLFWwindowWrapper* windowWrapper = static_cast<GLFWwindowWrapper*>(glfwGetWindowUserPointer(window));
            if (const auto& engineCallback = windowWrapper->GetEngineCallback(); engineCallback)
            {
                KeyTypedEvent event{static_cast<int>(codepoint)};
                engineCallback(event);
            }
        }
    );

    // Mouse
    // Mouse button
    glfwSetMouseButtonCallback(
        m_window,
        [](GLFWwindow* window, int button, int action, int /*mods*/)
        {
            GLFWwindowWrapper* windowWrapper = static_cast<GLFWwindowWrapper*>(glfwGetWindowUserPointer(window));
            if (const auto& engineCallback = windowWrapper->GetEngineCallback(); engineCallback)
            {
                switch (action)
                {
                    case GLFW_PRESS:
                    {
                        MouseButtonPressedEvent event{button};
                        engineCallback(event);
                        break;
                    }

                    case GLFW_RELEASE:
                    {
                        MouseButtonReleasedEvent event{button};
                        engineCallback(event);
                        break;
                    }

                    default:
                        break;
                }
            }
        }
    );

    // Mouse move
    glfwSetCursorPosCallback(
        m_window,
        [](GLFWwindow* window, double xpos, double ypos)
        {
            GLFWwindowWrapper* windowWrapper = static_cast<GLFWwindowWrapper*>(glfwGetWindowUserPointer(window));
            if (const auto& engineCallback = windowWrapper->GetEngineCallback(); engineCallback)
            {
                MouseMovedEvent event{xpos, ypos};
                engineCallback(event);
            }
        }
    );

    // Mouse scroll
    glfwSetScrollCallback(
        m_window,
        [](GLFWwindow* window, double xoffset, double yoffset)
        {
            GLFWwindowWrapper* windowWrapper = static_cast<GLFWwindowWrapper*>(glfwGetWindowUserPointer(window));
            if (const auto& engineCallback = windowWrapper->GetEngineCallback(); engineCallback)
            {
                MouseScrolledEvent event{xoffset, yoffset};
                engineCallback(event);
            }
        }
    );

    YAKO_INFO(
        Window, "Successfully created GLFW window '{}' (ID: {})", settings.m_title, static_cast<unsigned int>(id)
    );
}

GLFWwindowWrapper::~GLFWwindowWrapper()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
        YAKO_INFO(Window, "GLFW window destroyed.");
    }
}

void* GLFWwindowWrapper::GetNativeHandle() const
{
    return m_window;
}

bool GLFWwindowWrapper::IsValid() const
{
    return m_window != nullptr;
}

bool GLFWwindowWrapper::ShouldClose() const
{
    if (m_window)
    {
        return glfwWindowShouldClose(m_window);
    }
    else
    {
        YAKO_ERROR(Window, "Attempted to call ShouldClose() on an invalid or uninitialized window!");
        return true;
    }
}

void GLFWwindowWrapper::Open()
{
    if (!m_window)
    {
        YAKO_ERROR(Window, "Attempted to call Open() on an invalid window!");
        return;
    }
    glfwShowWindow(m_window);
}

void GLFWwindowWrapper::Hide()
{
    if (!m_window)
    {
        YAKO_ERROR(Window, "Attempted to call Hide() on an invalid window!");
        return;
    }
    glfwHideWindow(m_window);
}

void GLFWwindowWrapper::Close()
{
    if (!m_window)
    {
        YAKO_ERROR(Window, "Attempted to call Close() on an invalid window!");
        return;
    }

    Hide();
    glfwSetWindowShouldClose(m_window, true);
}

}  // namespace YakoEngine