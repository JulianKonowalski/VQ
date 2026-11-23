#pragma once

#include "vq/graphics/transform/IProjectionTransform.hpp"

namespace vq::graphics::transform {

/*----------------------------------------------------------------------------*/

class OrthographicProjectionTransform final : public IProjectionTransform {
  public:
    OrthographicProjectionTransform(const float scale,
                                    const float far_clip_distance,
                                    const float near_clip_distance,
                                    const float viewport_aspect_ratio);
    ~OrthographicProjectionTransform() = default;

    OrthographicProjectionTransform(OrthographicProjectionTransform&& other);
    OrthographicProjectionTransform(
        const OrthographicProjectionTransform& other);

    OrthographicProjectionTransform&
    operator=(OrthographicProjectionTransform&& other);
    OrthographicProjectionTransform&
    operator=(const OrthographicProjectionTransform& other);

    inline float get_scale() const;
    void set_scale(const float scale);

  protected:
    void on_update() override;

  private:
    float m_scale;
};

/*----------------------------------------------------------------------------*/

inline float OrthographicProjectionTransform::get_scale() const {
    return m_scale;
}

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::transform
