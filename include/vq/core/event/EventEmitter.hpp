#pragma once

#include "vq/core/event/IEventEmitter.hpp"
#include "vq/core/event/IEventHandler.hpp"

namespace vq::core::event {

/*----------------------------------------------------------------------------*/

template <typename... EventTypes>
class EventEmitter : private IEventEmitter<EventTypes>... {

    using ThisType = EventEmitter<EventTypes...>;

  public:
    EventEmitter()  = default;
    ~EventEmitter() = default;

    EventEmitter(ThisType&& other);
    EventEmitter(const ThisType& other);

    ThisType& operator=(ThisType&& other);
    ThisType& operator=(const ThisType& other);

    template <typename EventType>
    bool attach_event_handler(IEventHandler<EventType>& event_handler);

    template <typename EventType>
    bool detach_event_handler(IEventHandler<EventType>& event_handler);

  protected:
    template <typename EventType, typename... Args>
    void emit_event(Args&&... args);
};

/*----------------------------------------------------------------------------*/

template <typename... EventTypes>
EventEmitter<EventTypes...>::EventEmitter(ThisType&& other)
    : IEventEmitter<EventTypes>(std::move(other))... {}

template <typename... EventTypes>
EventEmitter<EventTypes...>::EventEmitter(const ThisType& other)
    : IEventEmitter<EventTypes>(other)... {}

template <typename... EventTypes>
EventEmitter<EventTypes...>&
EventEmitter<EventTypes...>::operator=(ThisType&& other) {
    (IEventEmitter<EventTypes>::operator=(std::move(other)), ...);
    return *this;
}

template <typename... EventTypes>
EventEmitter<EventTypes...>&
EventEmitter<EventTypes...>::operator=(const ThisType& other) {
    (IEventEmitter<EventTypes>::operator=(other), ...);
    return *this;
}

template <typename... EventTypes>
template <typename EventType>
bool EventEmitter<EventTypes...>::attach_event_handler(
    IEventHandler<EventType>& event_handler) {
    static_assert((std::is_same_v<EventType, EventTypes> || ...),
                  "EventType must be one of the allowed EventTypes");
    return IEventEmitter<EventType>::attach_event_handler(event_handler);
}

template <typename... EventTypes>
template <typename EventType>
bool EventEmitter<EventTypes...>::detach_event_handler(
    IEventHandler<EventType>& event_handler) {
    static_assert((std::is_same_v<EventType, EventTypes> || ...),
                  "EventType must be one of the allowed EventTypes");
    return IEventEmitter<EventType>::detach_event_handler(event_handler);
}

template <typename... EventTypes>
template <typename EventType, typename... Args>
void EventEmitter<EventTypes...>::emit_event(Args&&... args) {
    static_assert((std::is_same_v<EventType, EventTypes> || ...),
                  "EventType must be one of the allowed EventTypes");
    EventType event(args...);
    IEventEmitter<EventType>::emit_event(event);
}

/*----------------------------------------------------------------------------*/

} // namespace vq::core::event
