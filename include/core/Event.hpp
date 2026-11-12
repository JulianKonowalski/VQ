#pragma once

#include <type_traits>
#include <vector>

namespace vq::core {

/*----------------------------------------------------------------------------*/

template <typename EventType>
class EventHandlerBase;

/*----------------------------------------------------------------------------*/

class EventBase {
  public:
    inline EventBase();
    ~EventBase() = default;

    EventBase(EventBase&& other)                 = delete;
    EventBase(const EventBase& other)            = delete;
    EventBase& operator=(EventBase&& other)      = delete;
    EventBase& operator=(const EventBase& other) = delete;

    inline bool is_handled() const;
    inline void set_handled();

  private:
    bool m_is_handled;
};

/*----------------------------------------------------------------------------*/

template <typename EventType>
class EventEmitterBase {
    static_assert(std::is_base_of_v<EventBase, EventType>,
                  "EventType must derive from vq::core::EventBase");

    friend EventHandlerBase<EventType>;

    using ThisType = EventEmitterBase<EventType>;

  public:
    EventEmitterBase() = default;
    ~EventEmitterBase();

    EventEmitterBase(ThisType&& other);
    EventEmitterBase(const ThisType& other);

    ThisType& operator=(ThisType&& other);
    ThisType& operator=(const ThisType& other);

    bool attach_event_handler(EventHandlerBase<EventType>& event_handler);
    bool detach_event_handler(EventHandlerBase<EventType>& event_handler);

  protected:
    void emit_event(EventType& event);

  private:
    bool replace_event_handler(EventHandlerBase<EventType>& old_event_handler,
                               EventHandlerBase<EventType>& new_event_handler);

    std::vector<EventHandlerBase<EventType>*> m_event_handlers;
};

/*----------------------------------------------------------------------------*/

template <typename EventType>
class EventHandlerBase {
    static_assert(std::is_base_of_v<EventBase, EventType>,
                  "EventType must derive from vq::core::EventBase");

    friend EventEmitterBase<EventType>;

    using ThisType = EventHandlerBase<EventType>;

  public:
    EventHandlerBase() = default;
    ~EventHandlerBase();

    EventHandlerBase(ThisType&& other);
    EventHandlerBase(const ThisType& other);

    ThisType& operator=(ThisType&& other);
    ThisType& operator=(const ThisType& other);

  protected:
    virtual void handle(EventType& event) noexcept {}

  private:
    bool attach_event_emitter(EventEmitterBase<EventType>& event_emitter);
    bool detach_event_emitter(EventEmitterBase<EventType>& event_emitter);

    std::vector<EventEmitterBase<EventType>*> m_event_emitters;
};

/*----------------------------------------------------------------------------*/

template <typename... EventTypes>
class EventEmitter : private EventEmitterBase<EventTypes>... {

    using ThisType = EventEmitter<EventTypes...>;

  public:
    EventEmitter()  = default;
    ~EventEmitter() = default;

    EventEmitter(ThisType&& other);
    EventEmitter(const ThisType& other);

    ThisType& operator=(ThisType&& other);
    ThisType& operator=(const ThisType& other);

    template <typename EventType>
    bool attach_event_handler(EventHandlerBase<EventType>& event_handler);

    template <typename EventType>
    bool detach_event_handler(EventHandlerBase<EventType>& event_handler);

  protected:
    template <typename EventType, typename... Args>
    void emit_event(Args&&... args);
};

/*----------------------------------------------------------------------------*/

template <typename... EventTypes>
class EventHandler : public EventHandlerBase<EventTypes>... {

    using ThisType = EventHandler<EventTypes...>;

  public:
    EventHandler()  = default;
    ~EventHandler() = default;

    EventHandler(ThisType&& other);
    EventHandler(const ThisType& other);

    ThisType& operator=(ThisType&& other);
    ThisType& operator=(const ThisType& other);
};

/*----------------------------------------------------------------------------*/

inline EventBase::EventBase() : m_is_handled(false) {}

inline bool EventBase::is_handled() const { return m_is_handled; }

inline void EventBase::set_handled() { m_is_handled = true; }

/*----------------------------------------------------------------------------*/

template <typename EventType>
EventEmitterBase<EventType>::~EventEmitterBase() {
    for (auto* p_event_handler : m_event_handlers) {
        p_event_handler->detach_event_emitter(*this);
    }
}

template <typename EventType>
EventEmitterBase<EventType>::EventEmitterBase(ThisType&& other) {
    *this = std::move(other);
}

template <typename EventType>
EventEmitterBase<EventType>::EventEmitterBase(const ThisType& other) {
    *this = other;
}

template <typename EventType>
EventEmitterBase<EventType>&
EventEmitterBase<EventType>::operator=(ThisType&& other) {
    /**
     * Don't do a range-based for loop, as other.m_event_handlers is modified
     * and can lead to iterator invalidation
     */
    while (other.m_event_handlers.size() > 0) {
        auto* p_event_handler = other.m_event_handlers[0];
        this->attach_event_handler(*p_event_handler);
        other.detach_event_handler(*p_event_handler);
    }
    return *this;
}

template <typename EventType>
EventEmitterBase<EventType>&
EventEmitterBase<EventType>::operator=(const ThisType& other) {
    for (auto* p_event_handler : other.m_event_handlers) {
        this->attach_event_handler(*p_event_handler);
    }
    return *this;
}

template <typename EventType>
bool EventEmitterBase<EventType>::attach_event_handler(
    EventHandlerBase<EventType>& event_handler) {
    auto it =
        std::find_if(m_event_handlers.begin(), m_event_handlers.end(),
                     [&](auto* handler) { return handler == &event_handler; });
    if (it != m_event_handlers.end()) {
        return false;
    }
    m_event_handlers.push_back(&event_handler);
    event_handler.attach_event_emitter(*this);
    return true;
}

template <typename EventType>
bool EventEmitterBase<EventType>::detach_event_handler(
    EventHandlerBase<EventType>& event_handler) {
    auto it =
        std::find_if(m_event_handlers.begin(), m_event_handlers.end(),
                     [&](auto* handler) { return handler == &event_handler; });
    if (it == m_event_handlers.end()) {
        return false;
    }
    m_event_handlers.erase(it);
    event_handler.detach_event_emitter(*this);
    return true;
}

template <typename EventType>
void EventEmitterBase<EventType>::emit_event(EventType& event) {
    for (auto* event_handler : m_event_handlers) {
        event_handler->handle(event);
        if (event.is_handled()) {
            break;
        }
    }
}

template <typename EventType>
bool EventEmitterBase<EventType>::replace_event_handler(
    EventHandlerBase<EventType>& old_event_handler,
    EventHandlerBase<EventType>& new_event_handler) {
    auto it = std::find_if(
        m_event_handlers.begin(), m_event_handlers.end(),
        [&](auto* handler) { return handler == &old_event_handler; });
    if (it == m_event_handlers.end()) {
        return false;
    }
    *it = &new_event_handler;
    old_event_handler.detach_event_emitter(*this);
    new_event_handler.attach_event_emitter(*this);
    return true;
}

/*----------------------------------------------------------------------------*/

template <typename EventType>
EventHandlerBase<EventType>::~EventHandlerBase() {
    /**
     * Don't do a range-based for loop, as m_event_emitters is indirectly
     * modified and can lead to iterator invalidation
     */
    while (m_event_emitters.size() > 0) {
        m_event_emitters[0]->detach_event_handler(*this);
    }
}

template <typename EventType>
EventHandlerBase<EventType>::EventHandlerBase(ThisType&& other) {
    *this = std::move(other);
}

template <typename EventType>
EventHandlerBase<EventType>::EventHandlerBase(const ThisType& other) {
    *this = other;
}

template <typename EventType>
EventHandlerBase<EventType>&
EventHandlerBase<EventType>::operator=(ThisType&& other) {
    /**
     * Don't do a range-based for loop, as m_event_emitters is indirectly
     * modified and can lead to iterator invalidation
     */
    while (other.m_event_emitters.size() > 0) {
        other.m_event_emitters[0]->replace_event_handler(other, *this);
    }
    return *this;
}

template <typename EventType>
EventHandlerBase<EventType>&
EventHandlerBase<EventType>::operator=(const ThisType& other) {
    for (auto* p_event_emitter : other.m_event_emitters) {
        p_event_emitter->attach_event_handler(*this);
    }
    return *this;
}

template <typename EventType>
bool EventHandlerBase<EventType>::attach_event_emitter(
    EventEmitterBase<EventType>& event_emitter) {
    auto it =
        std::find_if(m_event_emitters.begin(), m_event_emitters.end(),
                     [&](auto* emitter) { return emitter == &event_emitter; });
    if (it != m_event_emitters.end()) {
        return false;
    }
    m_event_emitters.push_back(&event_emitter);
    return true;
}

template <typename EventType>
bool EventHandlerBase<EventType>::detach_event_emitter(
    EventEmitterBase<EventType>& event_emitter) {
    auto it =
        std::find_if(m_event_emitters.begin(), m_event_emitters.end(),
                     [&](auto* emitter) { return emitter == &event_emitter; });
    if (it == m_event_emitters.end()) {
        return false;
    }
    m_event_emitters.erase(it);
    return true;
}

/*----------------------------------------------------------------------------*/

template <typename... EventTypes>
EventEmitter<EventTypes...>::EventEmitter(ThisType&& other)
    : EventEmitterBase<EventTypes>(std::move(other))... {}

template <typename... EventTypes>
EventEmitter<EventTypes...>::EventEmitter(const ThisType& other)
    : EventEmitterBase<EventTypes>(other)... {}

template <typename... EventTypes>
EventEmitter<EventTypes...>&
EventEmitter<EventTypes...>::operator=(ThisType&& other) {
    (EventEmitterBase<EventTypes>::operator=(std::move(other)), ...);
    return *this;
}

template <typename... EventTypes>
EventEmitter<EventTypes...>&
EventEmitter<EventTypes...>::operator=(const ThisType& other) {
    (EventEmitterBase<EventTypes>::operator=(other), ...);
    return *this;
}

template <typename... EventTypes>
template <typename EventType>
bool EventEmitter<EventTypes...>::attach_event_handler(
    EventHandlerBase<EventType>& event_handler) {
    static_assert((std::is_same_v<EventType, EventTypes> || ...),
                  "EventType must be one of the allowed EventTypes");
    return EventEmitterBase<EventType>::attach_event_handler(event_handler);
}

template <typename... EventTypes>
template <typename EventType>
bool EventEmitter<EventTypes...>::detach_event_handler(
    EventHandlerBase<EventType>& event_handler) {
    static_assert((std::is_same_v<EventType, EventTypes> || ...),
                  "EventType must be one of the allowed EventTypes");
    return EventEmitterBase<EventType>::detach_event_handler(event_handler);
}

template <typename... EventTypes>
template <typename EventType, typename... Args>
void EventEmitter<EventTypes...>::emit_event(Args&&... args) {
    static_assert((std::is_same_v<EventType, EventTypes> || ...),
                  "EventType must be one of the allowed EventTypes");
    EventType event(args...);
    EventEmitterBase<EventType>::emit_event(event);
}

/*----------------------------------------------------------------------------*/

template <typename... EventTypes>
EventHandler<EventTypes...>::EventHandler(ThisType&& other)
    : EventHandlerBase<EventTypes>(std::move(other))... {}

template <typename... EventTypes>
EventHandler<EventTypes...>::EventHandler(const ThisType& other)
    : EventHandlerBase<EventTypes>(other)... {}

template <typename... EventTypes>
EventHandler<EventTypes...>&
EventHandler<EventTypes...>::operator=(ThisType&& other) {
    (EventHandlerBase<EventTypes>::operator=(std::move(other)), ...);
    return *this;
}

template <typename... EventTypes>
EventHandler<EventTypes...>&
EventHandler<EventTypes...>::operator=(const ThisType& other) {
    (EventHandlerBase<EventTypes>::operator=(other), ...);
    return *this;
}

/*----------------------------------------------------------------------------*/

} // namespace vq::core
