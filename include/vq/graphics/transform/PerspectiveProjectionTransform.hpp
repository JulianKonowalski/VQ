#pragma once

#include "vq/graphics/transform/IProjectionTransform.hpp"

namespace vq::graphics::transform {

/*----------------------------------------------------------------------------*/

class PerspectiveProjectionTransform final : public IProjectionTransform {
  public:
    PerspectiveProjectionTransform(const float field_of_view,
                                   const float far_clip_distance,
                                   const float near_clip_distance,
                                   const float viewport_aspect_ratio);
    ~PerspectiveProjectionTransform() = default;

    PerspectiveProjectionTransform(PerspectiveProjectionTransform&& other);
    PerspectiveProjectionTransform(const PerspectiveProjectionTransform& other);

    PerspectiveProjectionTransform&
    operator=(PerspectiveProjectionTransform&& other);
    PerspectiveProjectionTransform&
    operator=(const PerspectiveProjectionTransform& other);

    inline float get_field_of_view() const;
    void set_field_of_view(const float field_of_view);

  protected:
    void on_update() override;

  private:
    float m_field_of_view;
};

/*----------------------------------------------------------------------------*/

inline float PerspectiveProjectionTransform::get_field_of_view() const {
    return m_field_of_view;
}

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::transform
