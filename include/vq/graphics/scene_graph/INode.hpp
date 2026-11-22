#pragma once

#include <string>
#include <vector>

namespace vq::graphics::scene_graph {

/*----------------------------------------------------------------------------*/

class INode {
  public:
    INode(const std::string& name);
    virtual ~INode();

    /** TODO: implement this */
    INode(INode&&)                 = delete;
    INode(const INode&)            = delete;
    INode& operator=(INode&&)      = delete;
    INode& operator=(const INode&) = delete;

    inline const std::string& get_name() const;
    inline std::vector<INode*>& get_children();

    bool attach_child(INode* p_child);
    bool detach_child(INode* p_child);

  private:
    std::string m_name;
    std::vector<INode*> m_children;
};

/*----------------------------------------------------------------------------*/

inline const std::string& INode::get_name() const { return m_name; }

inline std::vector<INode*>& INode::get_children() { return m_children; }

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::scene_graph
