#pragma once

#include "vq/core/Resource.hpp"
#include "vq/graphics/geometry/Geometry.hpp"
#include "vq/graphics/scene_graph/INode.hpp"

namespace vq::graphics::scene_graph {

/*----------------------------------------------------------------------------*/

class GeometryNode final : public INode {
  public:
    GeometryNode(
        core::ResourceHandle<geometry::Geometry>&& geometry_resource_handle,
        const std::string& name);
    ~GeometryNode() override = default;

    /** TODO: implement this */
    GeometryNode(GeometryNode&& other)                 = delete;
    GeometryNode(const GeometryNode& other)            = delete;
    GeometryNode& operator=(GeometryNode&& other)      = delete;
    GeometryNode& operator=(const GeometryNode& other) = delete;

    inline const geometry::Geometry& get_geometry() const;

  private:
    const core::ResourceHandle<geometry::Geometry> m_geometry_resource_handle;
};

/*----------------------------------------------------------------------------*/

inline const geometry::Geometry& GeometryNode::get_geometry() const {
    return m_geometry_resource_handle.get();
}

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::scene_graph
