#include "Platform/Window/GLFW/GLFWwindowWrapper.h"
#include "Core/Log/Log.h"

#include <GLFW/glfw3.h>

namespace YakoEngine
{

GLFWwindowWrapper::GLFWwindowWrapper(const WindowSettings& settings, const WindowId& id)
    : IWindow(settings, id)
{
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