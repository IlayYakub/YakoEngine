#pragma once

#include "Utility/NonCopyableMoveable.h"

#include <functional>
#include <vector>
#include <unordered_map>
#include <expected>

namespace YakoEngine
{

struct SubscriberId final
{
    explicit SubscriberId(unsigned int value)
        : m_id(value)
    {
    }
    ~SubscriberId() = default;

    explicit operator unsigned int() const { return m_id; }

    auto operator<=>(const SubscriberId&) const = default;

    SubscriberId& operator++()
    {
        ++m_id;
        return *this;
    }

    SubscriberId operator++(int)
    {
        SubscriberId old = *this;
        ++m_id;
        return old;
    }

    unsigned int m_id{0};
};

enum class DelegateErrors
{
    EmptySubscriber,
    SubscriptionFailed,
    SubscriberNotFound
};

template <typename OwningType, typename... Args>
class ProtectedMulticastDelegate final : public NonCopyableMoveable
{
    using Subscriber = std::function<void(Args...)>;
    friend OwningType;

public:
    explicit ProtectedMulticastDelegate() = default;
    ~ProtectedMulticastDelegate()         = default;

    // Subscribe/Unsubscribe
    [[nodiscard]] std::expected<SubscriberId, DelegateErrors> AddSubscriber(Subscriber subscriber)
    {
        if (!subscriber)
        {
            return std::unexpected(DelegateErrors::EmptySubscriber);
        }

        const SubscriberId id = GenerateId();

        auto [it, inserted] = m_subscribers.emplace(id, std::move(subscriber));

        if (!inserted)
        {
            return std::unexpected(DelegateErrors::SubscriptionFailed);
        }

        return id;
    }

    std::expected<void, DelegateErrors> RemoveSubscriber(const SubscriberId& id)
    {
        if (m_subscribers.erase(id) == 0)
        {
            return std::unexpected(DelegateErrors::SubscriberNotFound);
        }
        return {};
    }

    void RemoveAllSubscribers() { m_subscribers.clear(); }

private:
    void Broadcast(Args... args) const
    {
        for (const auto& [id, subscriber] : m_subscribers)
        {
            if (subscriber)
            {
                subscriber(args...);
            }
        }
    }

    [[nodiscard]] SubscriberId GenerateId() const
    {
        static SubscriberId currentId{0};
        return currentId++;
    }

private:
    std::unordered_map<SubscriberId, Subscriber> m_subscribers;
};

}  // namespace YakoEngine

namespace std
{
template <>
struct hash<YakoEngine::SubscriberId>
{
    size_t operator()(const YakoEngine::SubscriberId& id) const noexcept { return std::hash<unsigned int>{}(id.m_id); }
};
}  // namespace std

#define DECLARE_PROTECTED_MULTICAST_DELEGATE(ownerClass, delegateName, ...) \
    ::YakoEngine::ProtectedMulticastDelegate<ownerClass __VA_OPT__(, ) __VA_ARGS__> delegateName