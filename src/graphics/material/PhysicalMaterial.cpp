#include "vq/graphics/material/PhysicalMaterial.hpp"

#include <glad/glad.h>

namespace vq::graphics::material {

/*----------------------------------------------------------------------------*/

PhysicalMaterial::PhysicalMaterial(const std::string& albedo_map_id,
                                   const std::string& normal_map_id,
                                   const std::string& metallic_map_id,
                                   const std::string& roughness_map_id)
    : m_albedo_map(core::resource::ResourceManager::get_instance()
                       .get_resource<texture::Texture2D>(albedo_map_id)),
      m_normal_map(core::resource::ResourceManager::get_instance()
                       .get_resource<texture::Texture2D>(normal_map_id)),
      m_metallic_map(core::resource::ResourceManager::get_instance()
                         .get_resource<texture::Texture2D>(metallic_map_id)),
      m_roughness_map(core::resource::ResourceManager::get_instance()
                          .get_resource<texture::Texture2D>(roughness_map_id)) {
}

/*----------------------------------------------------------------------------*/

void PhysicalMaterial::bind() {
    glActiveTexture(GL_TEXTURE0);
    m_albedo_map.get().bind();
    glActiveTexture(GL_TEXTURE1);
    if (m_normal_map.is_valid())
        m_normal_map.get().bind();
    glActiveTexture(GL_TEXTURE2);
    if (m_metallic_map.is_valid())
        m_metallic_map.get().bind();
    glActiveTexture(GL_TEXTURE3);
    if (m_roughness_map.is_valid())
        m_roughness_map.get().bind();
}

/*----------------------------------------------------------------------------*/

void PhysicalMaterial::unbind() {
    glActiveTexture(GL_TEXTURE0);
    m_albedo_map.get().unbind();
    glActiveTexture(GL_TEXTURE1);
    if (m_normal_map.is_valid())
        m_normal_map.get().unbind();
    glActiveTexture(GL_TEXTURE2);
    if (m_metallic_map.is_valid())
        m_metallic_map.get().unbind();
    glActiveTexture(GL_TEXTURE3);
    if (m_roughness_map.is_valid())
        m_roughness_map.get().unbind();
}

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::material
