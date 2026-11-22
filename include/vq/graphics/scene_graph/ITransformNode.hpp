#pragma once

#include "vq/graphics/scene_graph/INode.hpp"

#include <glm/mat4x4.hpp>

namespace vq::graphics::scene_graph {

/*----------------------------------------------------------------------------*/

class ITransformNode : public INode {
  public:
    ITransformNode(const std::string& name);

    virtual glm::mat4 get_transform_matrix() = 0;
};

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::scene_graph
