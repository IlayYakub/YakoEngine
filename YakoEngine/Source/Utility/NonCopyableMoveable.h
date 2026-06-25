#pragma once

namespace YakoEngine
{

class NonCopyableMoveable
{
public:
    explicit NonCopyableMoveable() = default;
    virtual ~NonCopyableMoveable() = default;

    // Copy = delete
    NonCopyableMoveable(const NonCopyableMoveable&)            = delete;
    NonCopyableMoveable& operator=(const NonCopyableMoveable&) = delete;

    // Move = delete
    NonCopyableMoveable(const NonCopyableMoveable&&)            = delete;
    NonCopyableMoveable& operator=(const NonCopyableMoveable&&) = delete;
};

}  // namespace YakoEngine