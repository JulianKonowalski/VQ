#pragma once

#include "vq/core/event/IEvent.hpp"
#include "vq/core/event/IEventEmitter.hpp"

#include <type_traits>
#include <vector>

namespace vq::core::event {

/*----------------------------------------------------------------------------*/

template <typename EventType>
class IEventHandler {
    static_assert(std::is_base_of_v<IEvent, EventType>,
                  "EventType must derive from vq::core::event::IEvent");

    friend IEventEmitter<EventType>;

    using ThisType = IEventHandler<EventType>;

  public:
    IEventHandler() = default;
    ~IEventHandler();

    IEventHandler(ThisType&& other);
    IEventHandler(const ThisType& other);

    ThisType& operator=(ThisType&& other);
    ThisType& operator=(const ThisType& other);

  protected:
    virtual void handle(EventType& event) noexcept {}

  private:
    bool attach_event_emitter(IEventEmitter<EventType>& event_emitter);
    bool detach_event_emitter(IEventEmitter<EventType>& event_emitter);

    std::vector<IEventEmitter<EventType>*> m_event_emitters;
};

/*----------------------------------------------------------------------------*/

template <typename EventType>
IEventHandler<EventType>::~IEventHandler() {
    /**
     * Don't do a range-based for loop, as m_event_emitters is indirectly
     * modified and can lead to iterator invalidation
     */
    while (m_event_emitters.size() > 0) {
        m_event_emitters[0]->detach_event_handler(*this);
    }
}

template <typename EventType>
IEventHandler<EventType>::IEventHandler(ThisType&& other) {
    *this = std::move(other);
}

template <typename EventType>
IEventHandler<EventType>::IEventHandler(const ThisType& other) {
    *this = other;
}

template <typename EventType>
IEventHandler<EventType>&
IEventHandler<EventType>::operator=(ThisType&& other) {
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
IEventHandler<EventType>&
IEventHandler<EventType>::operator=(const ThisType& other) {
    for (auto* p_event_emitter : other.m_event_emitters) {
        p_event_emitter->attach_event_handler(*this);
    }
    return *this;
}

template <typename EventType>
bool IEventHandler<EventType>::attach_event_emitter(
    IEventEmitter<EventType>& event_emitter) {
    auto it = std::find(m_event_emitters.begin(), m_event_emitters.end(),
                        &event_emitter);
    if (it != m_event_emitters.end()) {
        return false;
    }
    m_event_emitters.push_back(&event_emitter);
    return true;
}

template <typename EventType>
bool IEventHandler<EventType>::detach_event_emitter(
    IEventEmitter<EventType>& event_emitter) {
    auto it = std::find(m_event_emitters.begin(), m_event_emitters.end(),
                        &event_emitter);
    if (it == m_event_emitters.end()) {
        return false;
    }
    m_event_emitters.erase(it);
    return true;
}

/*----------------------------------------------------------------------------*/

} // namespace vq::core::event
