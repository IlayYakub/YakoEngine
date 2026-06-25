#pragma once

#include "Utility/NonCopyableMoveable.h"

#include <expected>

namespace YakoEngine
{

enum class SingletonWarnings
{
    COMMAND_IGNORED
};

template <typename T>
class Singleton : public NonCopyableMoveable
{
public:
    template <typename... Args>
    static std::expected<T*, SingletonWarnings> CreateInstance(Args&&... args)
    {
        if (!m_instance)
        {
            m_instance = new T(std::forward<Args>(args)...);
            return m_instance;
        }
        else
        {
            return std::unexpected(SingletonWarnings::COMMAND_IGNORED);
        }
    }

    static std::expected<T*, SingletonWarnings> GetInstance()
    {
        if (m_instance)
        {
            return m_instance;
        }
        else
        {
            return std::unexpected(SingletonWarnings::COMMAND_IGNORED);
        }
    }

protected:
    Singleton() = default;

protected:
    inline static T* m_instance = nullptr;
};

}  // namespace YakoEngine