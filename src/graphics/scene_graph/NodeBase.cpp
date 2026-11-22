#include "vq/graphics/scene_graph/NodeBase.hpp"

namespace vq::graphics::scene_graph {

/*----------------------------------------------------------------------------*/

NodeBase::NodeBase(const std::string& name) : m_name(name) {}

/*----------------------------------------------------------------------------*/

NodeBase::~NodeBase() {
    /**
     * TODO:
     * holy memory leaks
     * maybe change m_children to explicit non-owning pointers?
     */
}

/*----------------------------------------------------------------------------*/

bool NodeBase::attach_child(NodeBase* p_child) {
    auto it = std::find(m_children.begin(), m_children.end(), p_child);
    if (it != m_children.end()) {
        return false;
    }
    m_children.push_back(p_child);
    return true;
}

/*----------------------------------------------------------------------------*/

bool NodeBase::detach_child(NodeBase* p_child) {
    auto it = std::find(m_children.begin(), m_children.end(), p_child);
    if (it == m_children.end()) {
        return false;
    }
    m_children.erase(it);
    return true;
}

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::scene_graph
