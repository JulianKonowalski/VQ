#include "vq/graphics/transform/IProjectionTransform.hpp"

namespace vq::graphics::transform {

/*----------------------------------------------------------------------------*/

IProjectionTransform::IProjectionTransform(const float far_clip_distance,
                                           const float near_clip_distance,
                                           const float viewport_aspect_ratio)
    : m_far_clip_distance(far_clip_distance),
      m_near_clip_distance(near_clip_distance),
      m_viewport_aspect_ratio(viewport_aspect_ratio) {}

/*----------------------------------------------------------------------------*/

IProjectionTransform::IProjectionTransform(IProjectionTransform&& other)
    : ITransform(std::move(other)),
      m_far_clip_distance(other.m_far_clip_distance),
      m_near_clip_distance(other.m_near_clip_distance),
      m_viewport_aspect_ratio(other.m_viewport_aspect_ratio) {}

/*----------------------------------------------------------------------------*/

IProjectionTransform::IProjectionTransform(const IProjectionTransform& other)
    : ITransform(other), m_far_clip_distance(other.m_far_clip_distance),
      m_near_clip_distance(other.m_near_clip_distance),
      m_viewport_aspect_ratio(other.m_viewport_aspect_ratio) {}

/*----------------------------------------------------------------------------*/

IProjectionTransform&
IProjectionTransform::operator=(IProjectionTransform&& other) {
    m_far_clip_distance     = other.m_far_clip_distance;
    m_near_clip_distance    = other.m_near_clip_distance;
    m_viewport_aspect_ratio = other.m_viewport_aspect_ratio;
    ITransform::operator=(std::move(other));
    return *this;
}

/*----------------------------------------------------------------------------*/

IProjectionTransform&
IProjectionTransform::operator=(const IProjectionTransform& other) {
    m_far_clip_distance     = other.m_far_clip_distance;
    m_near_clip_distance    = other.m_near_clip_distance;
    m_viewport_aspect_ratio = other.m_viewport_aspect_ratio;
    ITransform::operator=(other);
    return *this;
}

/*----------------------------------------------------------------------------*/

void IProjectionTransform::set_far_clip_distance(
    const float far_clip_distance) {
    m_far_clip_distance = far_clip_distance;
    this->set_dirty();
}

/*----------------------------------------------------------------------------*/

void IProjectionTransform::set_near_clip_distance(
    const float near_clip_distance) {
    m_near_clip_distance = near_clip_distance;
    this->set_dirty();
}

/*----------------------------------------------------------------------------*/

void IProjectionTransform::set_viewport_aspect_ratio(
    const float viewport_aspect_ratio) {
    m_viewport_aspect_ratio = viewport_aspect_ratio;
    this->set_dirty();
}

/*----------------------------------------------------------------------------*/

/** reset shouldn't do anything on projection classes */
void IProjectionTransform::on_reset() {}

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::transform
