#pragma once

#include "Utility/NonCopyableMoveable.h"
#include "Platform/Window/IWindowManager.h"

#include <unordered_map>

namespace YakoEngine
{

class GLFWwindowWrapperManager final : public IWindowManager, NonCopyableMoveable
{
public:
    explicit GLFWwindowWrapperManager();
    virtual ~GLFWwindowWrapperManager();

    [[nodiscard]] virtual std::expected<WindowId, WindowManagerErrors> CreateWindow(
        const WindowSettings& settings
    ) override;
    [[nodiscard]] virtual std::expected<std::shared_ptr<IWindow>, WindowManagerErrors> GetWindowById(
        const WindowId& id
    ) override;
    [[nodiscard]] virtual bool AreAllWindowsClosed() const override;
    virtual void               OnUpdate() override;

private:
    void CleanupClosedWindows();

private:
    std::unordered_map<WindowId, std::shared_ptr<IWindow>> m_windowWrappers;
};

}  // namespace YakoEngine