#include "vq/graphics/scene_graph/Scene.hpp"

namespace vq::graphics::scene_graph {

/*----------------------------------------------------------------------------*/

Scene::Scene() : m_root_node("scene_root") {}

/*----------------------------------------------------------------------------*/

Scene::~Scene() {}

/*----------------------------------------------------------------------------*/

INode* Scene::find_node(const std::string& name) {
    auto traverse = [&](const auto& self, INode* p_node) -> INode* {
        if (!p_node) {
            return nullptr;
        }
        if (p_node->get_name() == name) {
            return p_node;
        }
        for (auto* p_child : p_node->get_children()) {
            INode* p_result = self(self, p_child);
            if (p_result) {
                return p_result;
            }
        }
        return nullptr;
    };
    return traverse(traverse, &m_root_node);
}

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::scene_graph
