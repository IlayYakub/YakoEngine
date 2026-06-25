#include "Platform/Window/GLFW/GLFWwindowWrapperManager.h"
#include "Platform/Window/GLFW/GLFWwindowWrapper.h"
#include "Core/Log/Log.h"

#include <GLFW/glfw3.h>

namespace YakoEngine
{

GLFWwindowWrapperManager::GLFWwindowWrapperManager()
{
    glfwSetErrorCallback([](int errorCode, const char* description)
                         { YAKO_ERROR(Window, "GLFW error, code: {}, description: {}", errorCode, description); });

    if (!glfwInit())
    {
        YAKO_ERROR(Window, "Failed to initialize GLFW via glfwInit()!");
        return;
    }

    YAKO_INFO(Window, "GLFW initialized successfully!");
    m_initialized = true;
}

GLFWwindowWrapperManager::~GLFWwindowWrapperManager()
{
    m_windowWrappers.clear();

    if (m_initialized)
    {
        glfwSetErrorCallback(nullptr);
        glfwTerminate();
    }

    m_initialized = false;
    YAKO_INFO(Window, "GLFW resources deallocated successfully!");
}

std::expected<WindowId, WindowManagerErrors> GLFWwindowWrapperManager::CreateWindow(const WindowSettings& settings)
{
    if (!m_initialized)
    {
        YAKO_ERROR(Window, "Failed to create window, GLFW is not initialized!");
        return std::unexpected(WindowManagerErrors::NOT_INITIALIZED);
    }

    auto window = std::make_shared<GLFWwindowWrapper>(settings, m_nextWindowId);
    if (!window->IsValid())
    {
        YAKO_ERROR(Window, "Failed to create window '{}', window is not valid!", settings.m_title);
        return std::unexpected(WindowManagerErrors::CANT_CREATE_WINDOW);
    }

    WindowId currentWindowId = m_nextWindowId;
    auto [it, inserted]      = m_windowWrappers.emplace(currentWindowId, std::move(window));
    if (!inserted)
    {
        YAKO_ERROR(Window, "Failed to insert window '{}' into manager map!", settings.m_title);
        return std::unexpected(WindowManagerErrors::CANT_CREATE_WINDOW);
    }

    ++m_nextWindowId;
    return currentWindowId;
}

std::shared_ptr<IWindow> GLFWwindowWrapperManager::GetWindowById(const WindowId& id)
{
    auto it = m_windowWrappers.find(id);
    if (it == m_windowWrappers.end())
    {
        YAKO_WARN(Window, "Window with ID {} not found!", static_cast<unsigned int>(id));
        return nullptr;
    }
    return it->second;
}

bool GLFWwindowWrapperManager::AreAllWindowsClosed() const
{
    return m_windowWrappers.empty();
}

void GLFWwindowWrapperManager::OnUpdate()
{
    if (!m_initialized)
        return;

    glfwPollEvents();
    CleanupClosedWindows();
}

void GLFWwindowWrapperManager::CleanupClosedWindows()
{
    for (auto it = m_windowWrappers.begin(); it != m_windowWrappers.end();)
    {
        if (it->second && it->second->ShouldClose())
        {
            YAKO_INFO(Window, "Removing closed window with ID {}", static_cast<unsigned int>(it->first));
            it = m_windowWrappers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

}  // namespace YakoEngine