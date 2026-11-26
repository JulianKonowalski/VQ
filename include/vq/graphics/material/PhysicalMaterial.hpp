#pragma once

#include "vq/core/resource/ResourceManager.hpp"
#include "vq/graphics/texture/Texture2D.hpp"

#include <string>

namespace vq::graphics::material {

/*----------------------------------------------------------------------------*/

class PhysicalMaterial final {
  public:
    PhysicalMaterial(const std::string& albedo_map_id,
                     const std::string& normal_map_id,
                     const std::string& metallic_map_id,
                     const std::string& roughness_map_id);
    ~PhysicalMaterial() = default;

    /** TODO: implement this */
    PhysicalMaterial(PhysicalMaterial&& other)                 = delete;
    PhysicalMaterial(const PhysicalMaterial& other)            = delete;
    PhysicalMaterial& operator=(PhysicalMaterial&& other)      = delete;
    PhysicalMaterial& operator=(const PhysicalMaterial& other) = delete;

    void bind();
    void unbind();

  private:
    core::resource::ResourceHandle<texture::Texture2D> m_albedo_map;
    core::resource::ResourceHandle<texture::Texture2D> m_normal_map;
    core::resource::ResourceHandle<texture::Texture2D> m_metallic_map;
    core::resource::ResourceHandle<texture::Texture2D> m_roughness_map;
};

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::material
