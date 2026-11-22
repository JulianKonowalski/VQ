#pragma once

#include <string>
#include <vector>

namespace vq::graphics::scene_graph {

/*----------------------------------------------------------------------------*/

class NodeBase {
  public:
    NodeBase(const std::string& name);
    virtual ~NodeBase();

    /** TODO: implement this */
    NodeBase(NodeBase&&)                 = delete;
    NodeBase(const NodeBase&)            = delete;
    NodeBase& operator=(NodeBase&&)      = delete;
    NodeBase& operator=(const NodeBase&) = delete;

    inline const std::string& get_name() const;
    inline std::vector<NodeBase*>& get_children();

    bool attach_child(NodeBase* p_child);
    bool detach_child(NodeBase* p_child);

  private:
    std::string m_name;
    std::vector<NodeBase*> m_children;
};

/*----------------------------------------------------------------------------*/

inline const std::string& NodeBase::get_name() const { return m_name; }

inline std::vector<NodeBase*>& NodeBase::get_children() { return m_children; }

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::scene_graph
