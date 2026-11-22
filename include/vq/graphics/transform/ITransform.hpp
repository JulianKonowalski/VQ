#pragma once

#include "vq/core/Event.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace vq::graphics::transform {

/*----------------------------------------------------------------------------*/

class ITransform;

/*----------------------------------------------------------------------------*/

struct TransformChangeEvent final : public vq::core::EventBase {
    explicit TransformChangeEvent(ITransform& transform)
        : transform(transform) {}
    ITransform& transform;
};

struct TransformResetEvent final : public vq::core::EventBase {
    explicit TransformResetEvent(ITransform& transform)
        : transform(transform) {}
    ITransform& transform;
};

struct TransformUpdateEvent final : public vq::core::EventBase {
    explicit TransformUpdateEvent(ITransform& transform)
        : transform(transform) {}
    ITransform& transform;
};

/*----------------------------------------------------------------------------*/

class ITransform
    : public vq::core::EventEmitter<TransformChangeEvent, TransformResetEvent,
                                    TransformUpdateEvent> {
  public:
    static constexpr glm::vec3 s_world_up     = {0.0f, 1.0f, 0.0f};
    static constexpr glm::vec3 s_world_front  = {0.0f, 0.0f, -1.0f};
    static constexpr glm::vec3 s_world_right  = {1.0f, 0.0f, 0.0f};
    static constexpr glm::vec3 s_world_center = {0.0f, 0.0f, 0.0f};

    ITransform();
    ~ITransform() = default;

    ITransform(ITransform&& other);
    ITransform(const ITransform& other);

    ITransform& operator=(ITransform&& other);
    ITransform& operator=(const ITransform& other);

    inline bool is_dirty() const;

    void reset_transform();
    void update_transform_matrix();

    const glm::mat4& get_transform_matrix();

  protected:
    virtual void on_reset()  = 0;
    virtual void on_update() = 0;

    void set_dirty();

    glm::mat4 m_transform_matrix;

  private:
    bool m_is_dirty;
};

/*----------------------------------------------------------------------------*/

inline bool ITransform::is_dirty() const { return m_is_dirty; }

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::transform
