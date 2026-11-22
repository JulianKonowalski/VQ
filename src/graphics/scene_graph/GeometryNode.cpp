#include "vq/graphics/scene_graph/GeometryNode.hpp"

namespace vq::graphics::scene_graph {

/*----------------------------------------------------------------------------*/

GeometryNode::GeometryNode(
    core::ResourceHandle<geometry::Geometry>&& geometry_resource_handle,
    const std::string& name)
    : NodeBase(name),
      m_geometry_resource_handle(std::move(geometry_resource_handle)) {}

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::scene_graph
