#pragma once

#include "vq/graphics/scene_graph/ITransformNode.hpp"
#include "vq/graphics/transform/RotateTransform.hpp"
#include "vq/graphics/transform/ScaleTransform.hpp"
#include "vq/graphics/transform/TranslateTransform.hpp"

namespace vq::graphics::scene_graph {

/*----------------------------------------------------------------------------*/

class WorldTransformNode final : public ITransformNode {
  public:
    WorldTransformNode(const std::string& name);
    ~WorldTransformNode() override = default;

    /** TODO: implement this */
    WorldTransformNode(WorldTransformNode&& other)                 = delete;
    WorldTransformNode(const WorldTransformNode& other)            = delete;
    WorldTransformNode& operator=(WorldTransformNode&& other)      = delete;
    WorldTransformNode& operator=(const WorldTransformNode& other) = delete;

    inline transform::ScaleTransform& get_scale_transform();
    inline transform::RotateTransform& get_rotate_transform();
    inline transform::TranslateTransform& get_translate_transform();

    glm::mat4 get_transform_matrix() override;

  private:
    transform::ScaleTransform m_scale_transform;
    transform::RotateTransform m_rotate_transform;
    transform::TranslateTransform m_translate_transform;
};

/*----------------------------------------------------------------------------*/

inline transform::ScaleTransform& WorldTransformNode::get_scale_transform() {
    return m_scale_transform;
}

inline transform::RotateTransform& WorldTransformNode::get_rotate_transform() {
    return m_rotate_transform;
}

inline transform::TranslateTransform&
WorldTransformNode::get_translate_transform() {
    return m_translate_transform;
}

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::scene_graph
