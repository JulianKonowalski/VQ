
#include "vq/graphics/scene_graph/WorldTransformNode.hpp"

namespace vq::graphics::scene_graph {

/*----------------------------------------------------------------------------*/

WorldTransformNode::WorldTransformNode(const std::string& name)
    : ITransformNode(name) {}

/*----------------------------------------------------------------------------*/

glm::mat4 WorldTransformNode::get_transform_matrix() {
    return m_translate_transform.get_transform_matrix() *
           m_rotate_transform.get_transform_matrix() *
           m_scale_transform.get_transform_matrix();
}

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::scene_graph
