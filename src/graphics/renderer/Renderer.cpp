#include "vq/graphics/renderer/Renderer.hpp"

#include "vq/core/resource/ResourceManager.hpp"
#include "vq/graphics/scene_graph/GeometryNode.hpp"
#include "vq/graphics/scene_graph/ITransformNode.hpp"
#include "vq/graphics/shader/Shader.hpp"

#include <glad/glad.h>

namespace vq::graphics::renderer {

/*----------------------------------------------------------------------------*/

/** TODO: maybe move this to a globally accessible location */
static const std::string s_base_resource_path = VQ_RESOURCE_PATH;

/*----------------------------------------------------------------------------*/

Renderer::Renderer() {
    auto& resource_manager = core::resource::ResourceManager::get_instance();
    resource_manager.load_resource<shader::Shader>(
        "pbr_master_shader",
        std::vector<shader::Shader::ShaderSourceFile>({
            {s_base_resource_path + "shaders/passthrough.vert.glsl",
             shader::Shader::ShaderSourceType::VERTEX},
            {s_base_resource_path + "shaders/passthrough.frag.glsl",
             shader::Shader::ShaderSourceType::FRAGMENT},
        }));
}

/*----------------------------------------------------------------------------*/

/**
 * Again, that's just brute forcing through the entire scene and forward
 * rendering whatever the renderer stumbles upon...
 * TODO: implement render commands, some kind of culling, sorting by depth,
 * shader etc
 */
void Renderer::render(scene_graph::Scene& scene) {
    auto* root_node = scene.get_root_node();
    static auto shader_handle =
        core::resource::ResourceManager::get_instance()
            .get_resource<shader::Shader>("pbr_master_shader");
    static auto model_matrix_uniform =
        shader_handle.get().get_uniform<glm::mat4>("u_model_matrix");

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    auto traverse = [&](const auto self, scene_graph::INode* p_node,
                        glm::mat4 transform) -> void {
        if (auto* p_casted = dynamic_cast<scene_graph::GeometryNode*>(p_node)) {
            const auto& geometry = p_casted->get_geometry();
            geometry.bind();
            model_matrix_uniform.set_value(transform);
            glDrawElements(GL_TRIANGLES, geometry.get_indices_size(),
                           GL_UNSIGNED_INT, nullptr);
            geometry.unbind();
        } else if (auto* p_casted =
                       dynamic_cast<scene_graph::ITransformNode*>(p_node)) {
            transform *= p_casted->get_transform_matrix();
        }
        for (auto* p_child : p_node->get_children()) {
            self(self, p_child, transform);
        }
    };

    shader_handle.get().bind();
    traverse(traverse, root_node, glm::mat4(1.0));
    shader_handle.get().unbind();
}

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::renderer
