#include "graphics/texture/Texture2D.hpp"

#include <glad/glad.h>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif

namespace vq::graphics::texture {

/*----------------------------------------------------------------------------*/

Texture2D::Texture2D(const std::string& id, const std::string& source_file)
    : Texture<vq::graphics::core::TextureType::TEXTURE_2D>(id, {source_file}) {}

/*----------------------------------------------------------------------------*/

Texture2D::Texture2D(Texture2D&& other)
    : Texture<vq::graphics::core::TextureType::TEXTURE_2D>(std::move(other)) {}

/*----------------------------------------------------------------------------*/

Texture2D& Texture2D::operator=(Texture2D&& other) {
    Texture<vq::graphics::core::TextureType::TEXTURE_2D>::operator=(
        std::move(other));
    return *this;
}

/*----------------------------------------------------------------------------*/

bool Texture2D::do_load() noexcept {
    glGenTextures(1, &m_texture_id);
    if (!m_texture_id) {
        return false;
    }

    auto* const current_texture = Texture2D::get_current();

    this->bind();
    this->set_wrap_s(vq::graphics::core::TextureWrapType::REPEAT);
    this->set_wrap_t(vq::graphics::core::TextureWrapType::REPEAT);
    this->set_filter_min(vq::graphics::core::TextureFilterType::LINEAR);
    this->set_filter_mag(vq::graphics::core::TextureFilterType::LINEAR);

    int width      = 0;
    int height     = 0;
    int components = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data =
        stbi_load(m_source_files[0].c_str(), &width, &height, &components, 4);
    if (!data) {
        current_texture ? current_texture->bind() : Texture2D::unbind_all();
        return false;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);

    current_texture ? current_texture->bind() : Texture2D::unbind_all();
    stbi_image_free(data);

    return true;
}

/*----------------------------------------------------------------------------*/

bool Texture2D::do_reload() noexcept { return true; }

/*----------------------------------------------------------------------------*/

void Texture2D::do_unload() noexcept {}

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::texture
