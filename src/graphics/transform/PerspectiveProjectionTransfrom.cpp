#include "vq/graphics/transform/PerspectiveProjectionTransform.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace vq::graphics::transform {

/*----------------------------------------------------------------------------*/

PerspectiveProjectionTransform::PerspectiveProjectionTransform(
    const float field_of_view, const float far_clip_distance,
    const float near_clip_distance, const float viewport_aspect_ratio)
    : IProjectionTransform(far_clip_distance, near_clip_distance,
                           viewport_aspect_ratio),
      m_field_of_view(field_of_view) {}

/*----------------------------------------------------------------------------*/

PerspectiveProjectionTransform::PerspectiveProjectionTransform(
    PerspectiveProjectionTransform&& other)
    : IProjectionTransform(std::move(other)),
      m_field_of_view(other.m_field_of_view) {}

/*----------------------------------------------------------------------------*/

PerspectiveProjectionTransform::PerspectiveProjectionTransform(
    const PerspectiveProjectionTransform& other)
    : IProjectionTransform(other), m_field_of_view(other.m_field_of_view) {}

/*----------------------------------------------------------------------------*/

PerspectiveProjectionTransform& PerspectiveProjectionTransform::operator=(
    PerspectiveProjectionTransform&& other) {
    m_field_of_view = other.m_field_of_view;
    IProjectionTransform::operator=(std::move(other));
    return *this;
}

/*----------------------------------------------------------------------------*/

PerspectiveProjectionTransform& PerspectiveProjectionTransform::operator=(
    const PerspectiveProjectionTransform& other) {
    m_field_of_view = other.m_field_of_view;
    IProjectionTransform::operator=(other);
    return *this;
}

/*----------------------------------------------------------------------------*/

void PerspectiveProjectionTransform::set_field_of_view(
    const float field_of_view) {
    m_field_of_view = field_of_view;
    this->set_dirty();
}

/*----------------------------------------------------------------------------*/

void PerspectiveProjectionTransform::on_update() {
    m_transform_matrix =
        glm::perspective(glm::radians(m_field_of_view), m_viewport_aspect_ratio,
                         m_near_clip_distance, m_far_clip_distance);
}

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::transform
