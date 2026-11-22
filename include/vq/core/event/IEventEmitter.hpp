#pragma once

#include "vq/core/event/IEvent.hpp"

#include <type_traits>
#include <vector>

namespace vq::core::event {

/*----------------------------------------------------------------------------*/

template <typename EventType>
class IEventHandler;

/*----------------------------------------------------------------------------*/

template <typename EventType>
class IEventEmitter {
    static_assert(std::is_base_of_v<IEvent, EventType>,
                  "EventType must derive from vq::core::event::IEvent");

    friend IEventHandler<EventType>;

    using ThisType = IEventEmitter<EventType>;

  public:
    IEventEmitter() = default;
    ~IEventEmitter();

    IEventEmitter(ThisType&& other);
    IEventEmitter(const ThisType& other);

    ThisType& operator=(ThisType&& other);
    ThisType& operator=(const ThisType& other);

    bool attach_event_handler(IEventHandler<EventType>& event_handler);
    bool detach_event_handler(IEventHandler<EventType>& event_handler);

  protected:
    void emit_event(EventType& event);

  private:
    bool replace_event_handler(IEventHandler<EventType>& old_event_handler,
                               IEventHandler<EventType>& new_event_handler);

    std::vector<IEventHandler<EventType>*> m_event_handlers;
};

/*----------------------------------------------------------------------------*/

template <typename EventType>
IEventEmitter<EventType>::~IEventEmitter() {
    for (auto* p_event_handler : m_event_handlers) {
        p_event_handler->detach_event_emitter(*this);
    }
}

template <typename EventType>
IEventEmitter<EventType>::IEventEmitter(ThisType&& other) {
    *this = std::move(other);
}

template <typename EventType>
IEventEmitter<EventType>::IEventEmitter(const ThisType& other) {
    *this = other;
}

template <typename EventType>
IEventEmitter<EventType>&
IEventEmitter<EventType>::operator=(ThisType&& other) {
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
IEventEmitter<EventType>&
IEventEmitter<EventType>::operator=(const ThisType& other) {
    for (auto* p_event_handler : other.m_event_handlers) {
        this->attach_event_handler(*p_event_handler);
    }
    return *this;
}

template <typename EventType>
bool IEventEmitter<EventType>::attach_event_handler(
    IEventHandler<EventType>& event_handler) {
    auto it = std::find(m_event_handlers.begin(), m_event_handlers.end(),
                        &event_handler);
    if (it != m_event_handlers.end()) {
        return false;
    }
    m_event_handlers.push_back(&event_handler);
    event_handler.attach_event_emitter(*this);
    return true;
}

template <typename EventType>
bool IEventEmitter<EventType>::detach_event_handler(
    IEventHandler<EventType>& event_handler) {
    auto it = std::find(m_event_handlers.begin(), m_event_handlers.end(),
                        &event_handler);
    if (it == m_event_handlers.end()) {
        return false;
    }
    m_event_handlers.erase(it);
    event_handler.detach_event_emitter(*this);
    return true;
}

template <typename EventType>
void IEventEmitter<EventType>::emit_event(EventType& event) {
    for (auto* event_handler : m_event_handlers) {
        event_handler->handle(event);
        if (event.is_handled()) {
            break;
        }
    }
}

template <typename EventType>
bool IEventEmitter<EventType>::replace_event_handler(
    IEventHandler<EventType>& old_event_handler,
    IEventHandler<EventType>& new_event_handler) {
    auto it = std::find(m_event_handlers.begin(), m_event_handlers.end(),
                        &old_event_handler);
    if (it == m_event_handlers.end()) {
        return false;
    }
    *it = &new_event_handler;
    old_event_handler.detach_event_emitter(*this);
    new_event_handler.attach_event_emitter(*this);
    return true;
}

/*----------------------------------------------------------------------------*/

} // namespace vq::core::event
