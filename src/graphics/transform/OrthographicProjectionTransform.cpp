#include "vq/graphics/transform/OrthographicProjectionTransform.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace vq::graphics::transform {

/*----------------------------------------------------------------------------*/

OrthographicProjectionTransform::OrthographicProjectionTransform(
    const float scale, const float far_clip_distance,
    const float near_clip_distance, const float viewport_aspect_ratio)
    : IProjectionTransform(far_clip_distance, near_clip_distance,
                           viewport_aspect_ratio),
      m_scale(scale) {}

/*----------------------------------------------------------------------------*/

OrthographicProjectionTransform::OrthographicProjectionTransform(
    OrthographicProjectionTransform&& other)
    : IProjectionTransform(std::move(other)), m_scale(other.m_scale) {}

/*----------------------------------------------------------------------------*/

OrthographicProjectionTransform::OrthographicProjectionTransform(
    const OrthographicProjectionTransform& other)
    : IProjectionTransform(other), m_scale(other.m_scale) {}

/*----------------------------------------------------------------------------*/

OrthographicProjectionTransform& OrthographicProjectionTransform::operator=(
    OrthographicProjectionTransform&& other) {
    m_scale = other.m_scale;
    IProjectionTransform::operator=(std::move(other));
    return *this;
}

/*----------------------------------------------------------------------------*/

OrthographicProjectionTransform& OrthographicProjectionTransform::operator=(
    const OrthographicProjectionTransform& other) {
    m_scale = other.m_scale;
    IProjectionTransform::operator=(other);
    return *this;
}

/*----------------------------------------------------------------------------*/

void OrthographicProjectionTransform::set_scale(const float scale) {
    m_scale = scale;
    this->set_dirty();
}

/*----------------------------------------------------------------------------*/

void OrthographicProjectionTransform::on_update() {
    const float horizontal_size = m_scale * m_viewport_aspect_ratio;
    m_transform_matrix =
        glm::ortho(-horizontal_size, horizontal_size, -m_scale, m_scale,
                   m_near_clip_distance, m_far_clip_distance);
}

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::transform
