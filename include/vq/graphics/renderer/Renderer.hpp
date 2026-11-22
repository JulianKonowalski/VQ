#pragma once

#include "vq/core/Resource.hpp"
#include "vq/graphics/scene_graph/Scene.hpp"
#include "vq/graphics/shader/Shader.hpp"

namespace vq::graphics::renderer {

/*----------------------------------------------------------------------------*/

/**
 * This is EXTREMELY primitive - for now I just want it to render something,
 * hiding the OpenGL API
 */
class Renderer final {
  public:
    Renderer();
    ~Renderer() = default;

    void render(scene_graph::Scene& scene);
};

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::renderer
