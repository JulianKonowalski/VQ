#pragma once

#include "vq/graphics/scene_graph/INode.hpp"

namespace vq::graphics::scene_graph {

/*----------------------------------------------------------------------------*/

class Scene final {
  public:
    Scene();
    ~Scene();

    /** TODO: implement this */
    Scene(Scene&& other)                 = delete;
    Scene(const Scene& other)            = delete;
    Scene& operator=(Scene&& other)      = delete;
    Scene& operator=(const Scene& other) = delete;

    inline INode* get_root_node();
    INode* find_node(const std::string& name);

  private:
    INode m_root_node;
};

/*----------------------------------------------------------------------------*/

inline INode* Scene::get_root_node() { return &m_root_node; }

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::scene_graph
