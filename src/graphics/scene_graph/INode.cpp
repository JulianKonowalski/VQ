#include "vq/graphics/scene_graph/INode.hpp"

namespace vq::graphics::scene_graph {

/*----------------------------------------------------------------------------*/

INode::INode(const std::string& name) : m_name(name) {}

/*----------------------------------------------------------------------------*/

INode::~INode() {
    /**
     * TODO:
     * holy memory leaks
     * maybe change m_children to explicit non-owning pointers?
     */
}

/*----------------------------------------------------------------------------*/

bool INode::attach_child(INode* p_child) {
    auto it = std::find(m_children.begin(), m_children.end(), p_child);
    if (it != m_children.end()) {
        return false;
    }
    m_children.push_back(p_child);
    return true;
}

/*----------------------------------------------------------------------------*/

bool INode::detach_child(INode* p_child) {
    auto it = std::find(m_children.begin(), m_children.end(), p_child);
    if (it == m_children.end()) {
        return false;
    }
    m_children.erase(it);
    return true;
}

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::scene_graph
