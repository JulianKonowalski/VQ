#pragma once

#include "vq/core/Event.hpp"

#include <cstdint>

namespace vq::io {

/*----------------------------------------------------------------------------*/

class Window;

/*----------------------------------------------------------------------------*/

struct KeyEvent : public vq::core::EventBase {
    explicit KeyEvent(Window& window, int key, int scancode, int action,
                      int mods)
        : window(window), key(key), scancode(scancode), action(action),
          mods(mods) {}

    Window& window;
    const int key;
    const int scancode;
    const int action;
    const int mods;
};

struct MouseScrollEvent : public vq::core::EventBase {
    explicit MouseScrollEvent(Window& window, double scroll_x_offset,
                              double scroll_y_offset)
        : window(window), scroll_x_offset(scroll_x_offset),
          scroll_y_offset(scroll_y_offset) {}

    Window& window;
    const double scroll_x_offset;
    const double scroll_y_offset;
};

struct MouseButtonEvent : public vq::core::EventBase {
    explicit MouseButtonEvent(Window& window, int button, int action, int mods)
        : window(window), button(button), action(action), mods(mods) {}

    Window& window;
    const int button;
    const int action;
    const int mods;
};

struct MouseMoveEvent : public vq::core::EventBase {
    explicit MouseMoveEvent(Window& window, const double x_position_delta,
                            const double y_position_delta)
        : window(window), x_position_delta(x_position_delta),
          y_position_delta(y_position_delta) {}

    Window& window;
    const double x_position_delta;
    const double y_position_delta;
};

struct MouseDragEvent : public vq::core::EventBase {
    explicit MouseDragEvent(Window& window, const double x_position_delta,
                            const double y_position_delta)
        : window(window), x_position_delta(x_position_delta),
          y_position_delta(y_position_delta) {}

    Window& window;
    const double x_position_delta;
    const double y_position_delta;
};

struct WindowResizeEvent : public vq::core::EventBase {
    explicit WindowResizeEvent(Window& window, int width, int height)
        : window(window), width(width), height(height) {}

    Window& window;
    const int width;
    const int height;
};

/*----------------------------------------------------------------------------*/

class Window final
    : public vq::core::EventEmitter<KeyEvent, MouseScrollEvent,
                                    MouseButtonEvent, MouseMoveEvent,
                                    MouseDragEvent, WindowResizeEvent> {
  public:
    struct WindowSpecification {
        WindowSpecification()
            : title("OpenGL Window"), width(800), height(600) {}

        WindowSpecification(const char* const title, int width = 800,
                            int height = 600)
            : title(title), width(width), height(height) {}

        const char* const title;
        int width;
        int height;
    };

    struct MouseState {
        MouseState() : x_position(0.0), y_position(0.0), mods(0), buttons(0) {}

        double x_position;
        double y_position;
        int mods;
        uint8_t buttons;
    };

    static void unbind_all();
    static Window* get_current();

    explicit Window(const WindowSpecification& window_specification =
                        WindowSpecification());
    Window(Window& other)  = delete;
    Window(Window&& other) = delete;
    ~Window();

    inline const WindowSpecification& get_specification() const {
        return m_specification;
    }

    inline const MouseState& get_mouse_state() const { return m_mouse_state; }

    void close();
    void update();
    void make_current();
    bool should_close();

    friend void vq_io_window_key_callback(Window& window, int key, int scancode,
                                          int action, int mods);

    friend void vq_io_window_scroll_callback(Window& window, double x_offset,
                                             double y_offset);

    friend void vq_io_window_mouse_button_callback(Window& window, int button,
                                                   int action, int mods);

    friend void vq_io_window_cursor_pos_callback(Window& window,
                                                 double x_position,
                                                 double y_position);

    friend void vq_io_window_framebuffer_size_callback(Window& window,
                                                       int width, int height);

  private:
    void* m_glfw_window;
    MouseState m_mouse_state;
    WindowSpecification m_specification;
};

/*----------------------------------------------------------------------------*/

} // namespace vq::io
