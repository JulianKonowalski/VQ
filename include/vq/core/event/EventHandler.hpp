#pragma once

#include "vq/core/event/IEventHandler.hpp"

namespace vq::core::event {

/*----------------------------------------------------------------------------*/

template <typename... EventTypes>
class EventHandler : public IEventHandler<EventTypes>... {

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

template <typename... EventTypes>
EventHandler<EventTypes...>::EventHandler(ThisType&& other)
    : IEventHandler<EventTypes>(std::move(other))... {}

template <typename... EventTypes>
EventHandler<EventTypes...>::EventHandler(const ThisType& other)
    : IEventHandler<EventTypes>(other)... {}

template <typename... EventTypes>
EventHandler<EventTypes...>&
EventHandler<EventTypes...>::operator=(ThisType&& other) {
    (IEventHandler<EventTypes>::operator=(std::move(other)), ...);
    return *this;
}

template <typename... EventTypes>
EventHandler<EventTypes...>&
EventHandler<EventTypes...>::operator=(const ThisType& other) {
    (IEventHandler<EventTypes>::operator=(other), ...);
    return *this;
}

/*----------------------------------------------------------------------------*/

} // namespace vq::core::event
