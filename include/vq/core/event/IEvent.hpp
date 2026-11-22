#pragma once

namespace vq::core::event {

/*----------------------------------------------------------------------------*/

class IEvent {
  public:
    inline IEvent();
    ~IEvent() = default;

    IEvent(IEvent&& other)                 = delete;
    IEvent(const IEvent& other)            = delete;
    IEvent& operator=(IEvent&& other)      = delete;
    IEvent& operator=(const IEvent& other) = delete;

    inline bool is_handled() const;
    inline void set_handled();

  private:
    bool m_is_handled;
};

/*----------------------------------------------------------------------------*/

inline IEvent::IEvent() : m_is_handled(false) {}

inline bool IEvent::is_handled() const { return m_is_handled; }

inline void IEvent::set_handled() { m_is_handled = true; }

/*----------------------------------------------------------------------------*/

} // namespace vq::core::event
