#pragma once

#include "vq/graphics/scene_graph/ITransformNode.hpp"
#include "vq/graphics/transform/IProjectionTransform.hpp"
#include "vq/graphics/transform/RotateTransform.hpp"
#include "vq/graphics/transform/TranslateTransform.hpp"
#include "vq/graphics/transform/ViewTransform.hpp"

#include <type_traits>

namespace vq::graphics::scene_graph {

/*----------------------------------------------------------------------------*/

template <typename ProjectionTransformType>
class CameraTransformNode final : public ITransformNode {
    static_assert(std::is_base_of_v<transform::IProjectionTransform,
                                    ProjectionTransformType>,
                  "ProjectionTransformType must derive from "
                  "vq::graphics::transform::IProjectionTransform class");

    using ThisType = CameraTransformNode<ProjectionTransformType>;

  public:
    template <typename... Args>
    CameraTransformNode(const std::string& name, Args&&...);
    ~CameraTransformNode() override = default;

    /** TODO: implement this */
    CameraTransformNode(ThisType&& other)      = delete;
    CameraTransformNode(const ThisType& other) = delete;
    ThisType& operator=(ThisType&& other)      = delete;
    ThisType& operator=(const ThisType& other) = delete;

    inline transform::ViewTransform& get_view_transform();
    inline ProjectionTransformType& get_projection_transform();
    inline const transform::ViewTransform& get_view_transform() const;
    inline const ProjectionTransformType& get_projection_transform() const;

    glm::mat4 get_transform_matrix() override;

  private:
    transform::RotateTransform m_rotate_transform;
    transform::TranslateTransform m_translate_transform;
    transform::ViewTransform m_view_transform;
    ProjectionTransformType m_projection_transform;
};

/*----------------------------------------------------------------------------*/

template <typename ProjectionTransformType>
template <typename... Args>
CameraTransformNode<ProjectionTransformType>::CameraTransformNode(
    const std::string& name, Args&&... args)
    : ITransformNode(name),
      m_view_transform(m_rotate_transform, m_translate_transform),
      m_projection_transform(args...) {}

template <typename ProjectionTransformType>
inline transform::ViewTransform&
CameraTransformNode<ProjectionTransformType>::get_view_transform() {
    return m_view_transform;
}

template <typename ProjectionTransformType>
inline ProjectionTransformType&
CameraTransformNode<ProjectionTransformType>::get_projection_transform() {
    return m_projection_transform;
}

template <typename ProjectionTransformType>
inline const transform::ViewTransform&
CameraTransformNode<ProjectionTransformType>::get_view_transform() const {
    return m_view_transform;
}

template <typename ProjectionTransformType>
inline const ProjectionTransformType&
CameraTransformNode<ProjectionTransformType>::get_projection_transform() const {
    return m_projection_transform;
}

template <typename ProjectionTransformType>
glm::mat4 CameraTransformNode<ProjectionTransformType>::get_transform_matrix() {
    return m_projection_transform.get_transform_matrix() *
           m_view_transform.get_transform_matrix();
}

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::scene_graph
