#pragma once

#include "vq/graphics/transform/ITransform.hpp"

namespace vq::graphics::transform {

/*----------------------------------------------------------------------------*/

class IProjectionTransform : public ITransform {
  public:
    explicit IProjectionTransform(const float far_clip_distance,
                                  const float near_clip_distance,
                                  const float viewport_aspect_ratio);
    ~IProjectionTransform() = default;

    IProjectionTransform(IProjectionTransform&& other);
    IProjectionTransform(const IProjectionTransform& other);

    IProjectionTransform& operator=(IProjectionTransform&& other);
    IProjectionTransform& operator=(const IProjectionTransform& other);

    inline float get_far_clip_distance() const;
    inline float get_near_clip_distance() const;
    inline float get_viewport_aspect_ratio() const;

    void set_far_clip_distance(const float far_clip_distance);
    void set_near_clip_distance(const float near_clip_distance);
    void set_viewport_aspect_ratio(const float viewport_aspect_ratio);

  protected:
    void on_reset() override;

    float m_far_clip_distance;
    float m_near_clip_distance;
    float m_viewport_aspect_ratio;
};

/*----------------------------------------------------------------------------*/

inline float IProjectionTransform::get_far_clip_distance() const {
    return m_far_clip_distance;
}

inline float IProjectionTransform::get_near_clip_distance() const {
    return m_near_clip_distance;
}

inline float IProjectionTransform::get_viewport_aspect_ratio() const {
    return m_viewport_aspect_ratio;
}

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::transform
