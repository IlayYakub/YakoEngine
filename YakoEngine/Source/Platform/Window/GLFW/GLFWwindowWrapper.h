#pragma once

#include "Utility/NonCopyableMoveable.h"
#include "Platform/Window/IWindow.h"

struct GLFWwindow;

namespace YakoEngine
{

class GLFWwindowWrapper final : public IWindow, NonCopyableMoveable
{
public:
    explicit GLFWwindowWrapper(const WindowSettings& settings, const WindowId& id);
    virtual ~GLFWwindowWrapper();

    [[nodiscard]] virtual void* GetNativeHandle() const override;
    [[nodiscard]] virtual bool  IsValid() const override;
    [[nodiscard]] virtual bool  ShouldClose() const override;
    virtual void                Open() override;
    virtual void                Hide() override;
    virtual void                Close() override;

private:
    GLFWwindow* m_window{nullptr};
};

}  // namespace YakoEngine