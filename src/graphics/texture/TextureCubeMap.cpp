#include "graphics/texture/TextureCubeMap.hpp"

#include <glad/glad.h>
#include <stb_image.h>

using namespace vq::graphics::texture;

/*----------------------------------------------------------------------------*/

TextureCubeMap::TextureCubeMap(const std::string& id,
                               const std::string& source_file_right,
                               const std::string& source_file_left,
                               const std::string& source_file_top,
                               const std::string& source_file_bottom,
                               const std::string& source_file_front,
                               const std::string& source_file_back)
    : Texture<vq::graphics::core::TextureType::TEXTURE_CUBE_MAP>(
          id, std::vector<std::string>(
                  {source_file_right, source_file_left, source_file_top,
                   source_file_bottom, source_file_front, source_file_back})) {}

/*----------------------------------------------------------------------------*/

TextureCubeMap::TextureCubeMap(TextureCubeMap&& other)
    : Texture<vq::graphics::core::TextureType::TEXTURE_CUBE_MAP>(
          std::move(other)) {}

/*----------------------------------------------------------------------------*/

TextureCubeMap& TextureCubeMap::operator=(TextureCubeMap&& other) {
    Texture<vq::graphics::core::TextureType::TEXTURE_CUBE_MAP>::operator=(
        std::move(other));
    return *this;
}

/*----------------------------------------------------------------------------*/

bool TextureCubeMap::do_load() noexcept {
    glGenTextures(1, &m_texture_id);
    if (!m_texture_id) {
        return false;
    }

    auto* const current_texture = TextureCubeMap::get_current();

    this->bind();
    this->set_wrap_s(vq::graphics::core::TextureWrapType::CLAMP_TO_EDGE);
    this->set_wrap_t(vq::graphics::core::TextureWrapType::CLAMP_TO_EDGE);
    this->set_wrap_r(vq::graphics::core::TextureWrapType::CLAMP_TO_EDGE);
    this->set_filter_min(vq::graphics::core::TextureFilterType::LINEAR);
    this->set_filter_mag(vq::graphics::core::TextureFilterType::LINEAR);

    int width           = 0;
    int height          = 0;
    int components      = 0;
    unsigned char* data = nullptr;

    stbi_set_flip_vertically_on_load(false);
    for (int i = 0; i < 6; ++i) {
        data = stbi_load(m_source_files[i].c_str(), &width, &height,
                         &components, 4);
        if (!data) {
            current_texture ? current_texture->bind()
                            : TextureCubeMap::unbind_all();
            return false;
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width,
                     height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
        data = nullptr;
    }

    current_texture ? current_texture->bind() : TextureCubeMap::unbind_all();

    return true;
}

/*----------------------------------------------------------------------------*/

bool TextureCubeMap::do_reload() noexcept { return true; }

/*----------------------------------------------------------------------------*/

void TextureCubeMap::do_unload() noexcept {}

/*----------------------------------------------------------------------------*/
