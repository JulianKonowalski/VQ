#include "graphics/core/Texture.hpp"

#include <glad/glad.h>

namespace vq::graphics::core {

/*----------------------------------------------------------------------------*/

template <TextureType TType>
struct TextureTypeLUT;

template <>
struct TextureTypeLUT<TextureType::TEXTURE_1D> {
    static constexpr unsigned int s_value = GL_TEXTURE_1D;
};

template <>
struct TextureTypeLUT<TextureType::TEXTURE_2D> {
    static constexpr unsigned int s_value = GL_TEXTURE_2D;
};

template <>
struct TextureTypeLUT<TextureType::TEXTURE_3D> {
    static constexpr unsigned int s_value = GL_TEXTURE_3D;
};

template <>
struct TextureTypeLUT<TextureType::TEXTURE_CUBE_MAP> {
    static constexpr unsigned int s_value = GL_TEXTURE_CUBE_MAP;
};

/*----------------------------------------------------------------------------*/

template <TextureType TType>
Texture<TType>::Texture(const std::string& id,
                        const std::vector<std::string>& source_files)
    : Resource(id), m_source_files(source_files), m_texture_id(0) {}

/*----------------------------------------------------------------------------*/

template <TextureType TType>
Texture<TType>::Texture(Texture<TType>&& other)
    : Resource(std::move(other)),
      m_source_files(std::move(other.m_source_files)),
      m_texture_id(other.m_texture_id) {
    other.m_texture_id = 0;
    s_current_texture  = s_current_texture == &other ? this : s_current_texture;
}

/*----------------------------------------------------------------------------*/

template <TextureType TType>
Texture<TType>& Texture<TType>::operator=(Texture<TType>&& other) {
    m_source_files     = std::move(other.m_source_files);
    m_texture_id       = other.m_texture_id;
    other.m_texture_id = 0;
    s_current_texture  = s_current_texture == &other ? this : s_current_texture;
    Resource::operator=(std::move(other));
    return *this;
}

/*----------------------------------------------------------------------------*/

template <TextureType TType>
void Texture<TType>::unbind_all() {
    glBindTexture(TextureTypeLUT<TType>::s_value, GL_NONE);
    s_current_texture = nullptr;
}

/*----------------------------------------------------------------------------*/

template <TextureType TType>
void Texture<TType>::set_wrap_s(const TextureWrapType wrap_type) {
    auto* const current_texture = s_current_texture;
    if (current_texture != this) {
        this->bind();
    }

    switch (wrap_type) {
    case TextureWrapType::REPEAT:
        glTexParameteri(TextureTypeLUT<TType>::s_value, GL_TEXTURE_WRAP_S,
                        GL_REPEAT);
        break;
    case TextureWrapType::MIRROR_REPEAT:
        glTexParameteri(TextureTypeLUT<TType>::s_value, GL_TEXTURE_WRAP_S,
                        GL_MIRRORED_REPEAT);
        break;
    case TextureWrapType::CLAMP_TO_EDGE:
        glTexParameteri(TextureTypeLUT<TType>::s_value, GL_TEXTURE_WRAP_S,
                        GL_CLAMP_TO_EDGE);
        break;
    case TextureWrapType::MIRROR_CLAMP_TO_EDGE:
        glTexParameteri(TextureTypeLUT<TType>::s_value, GL_TEXTURE_WRAP_S,
                        GL_MIRROR_CLAMP_TO_EDGE);
        break;
    case TextureWrapType::CLAMP_TO_BORDER:
        glTexParameteri(TextureTypeLUT<TType>::s_value, GL_TEXTURE_WRAP_S,
                        GL_CLAMP_TO_BORDER);
        break;
    }

    if (current_texture && current_texture != this) {
        current_texture->bind();
    }
}

/*----------------------------------------------------------------------------*/

template <TextureType TType>
void Texture<TType>::set_wrap_t(const TextureWrapType wrap_type) {
    auto* const current_texture = s_current_texture;
    if (current_texture != this) {
        this->bind();
    }

    switch (wrap_type) {
    case TextureWrapType::REPEAT:
        glTexParameteri(TextureTypeLUT<TType>::s_value, GL_TEXTURE_WRAP_T,
                        GL_REPEAT);
        break;
    case TextureWrapType::MIRROR_REPEAT:
        glTexParameteri(TextureTypeLUT<TType>::s_value, GL_TEXTURE_WRAP_T,
                        GL_MIRRORED_REPEAT);
        break;
    case TextureWrapType::CLAMP_TO_EDGE:
        glTexParameteri(TextureTypeLUT<TType>::s_value, GL_TEXTURE_WRAP_T,
                        GL_CLAMP_TO_EDGE);
        break;
    case TextureWrapType::MIRROR_CLAMP_TO_EDGE:
        glTexParameteri(TextureTypeLUT<TType>::s_value, GL_TEXTURE_WRAP_T,
                        GL_MIRROR_CLAMP_TO_EDGE);
        break;
    case TextureWrapType::CLAMP_TO_BORDER:
        glTexParameteri(TextureTypeLUT<TType>::s_value, GL_TEXTURE_WRAP_T,
                        GL_CLAMP_TO_BORDER);
        break;
    }

    if (current_texture && current_texture != this) {
        current_texture->bind();
    }
}

/*----------------------------------------------------------------------------*/

template <TextureType TType>
void Texture<TType>::set_wrap_r(const TextureWrapType wrap_type) {
    auto* const current_texture = s_current_texture;
    if (current_texture != this) {
        this->bind();
    }

    switch (wrap_type) {
    case TextureWrapType::REPEAT:
        glTexParameteri(TextureTypeLUT<TType>::s_value, GL_TEXTURE_WRAP_R,
                        GL_REPEAT);
        break;
    case TextureWrapType::MIRROR_REPEAT:
        glTexParameteri(TextureTypeLUT<TType>::s_value, GL_TEXTURE_WRAP_R,
                        GL_MIRRORED_REPEAT);
        break;
    case TextureWrapType::CLAMP_TO_EDGE:
        glTexParameteri(TextureTypeLUT<TType>::s_value, GL_TEXTURE_WRAP_R,
                        GL_CLAMP_TO_EDGE);
        break;
    case TextureWrapType::MIRROR_CLAMP_TO_EDGE:
        glTexParameteri(TextureTypeLUT<TType>::s_value, GL_TEXTURE_WRAP_R,
                        GL_MIRROR_CLAMP_TO_EDGE);
        break;
    case TextureWrapType::CLAMP_TO_BORDER:
        glTexParameteri(TextureTypeLUT<TType>::s_value, GL_TEXTURE_WRAP_R,
                        GL_CLAMP_TO_BORDER);
        break;
    }

    if (current_texture && current_texture != this) {
        current_texture->bind();
    }
}

/*----------------------------------------------------------------------------*/

template <TextureType TType>
void Texture<TType>::set_filter_min(const TextureFilterType filter_type) {
    auto* const current_texture = s_current_texture;
    if (current_texture != this) {
        this->bind();
    }

    switch (filter_type) {
    case TextureFilterType::LINEAR:
        glTexParameteri(TextureTypeLUT<TType>::s_value, GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR);
        break;
    case TextureFilterType::NEAREST:
        glTexParameteri(TextureTypeLUT<TType>::s_value, GL_TEXTURE_MIN_FILTER,
                        GL_NEAREST);
        break;
    }

    if (current_texture && current_texture != this) {
        current_texture->bind();
    }
}

/*----------------------------------------------------------------------------*/

template <TextureType TType>
void Texture<TType>::set_filter_mag(const TextureFilterType filter_type) {
    auto* const current_texture = s_current_texture;
    if (current_texture != this) {
        this->bind();
    }

    switch (filter_type) {
    case TextureFilterType::LINEAR:
        glTexParameteri(TextureTypeLUT<TType>::s_value, GL_TEXTURE_MAG_FILTER,
                        GL_LINEAR);
        break;
    case TextureFilterType::NEAREST:
        glTexParameteri(TextureTypeLUT<TType>::s_value, GL_TEXTURE_MAG_FILTER,
                        GL_NEAREST);
        break;
    }

    if (current_texture && current_texture != this) {
        current_texture->bind();
    }
}

/*----------------------------------------------------------------------------*/

template <TextureType TType>
void Texture<TType>::bind() {
    glBindTexture(TextureTypeLUT<TType>::s_value, m_texture_id);
    s_current_texture = this;
}

/*----------------------------------------------------------------------------*/

template <TextureType TType>
void Texture<TType>::unbind() {
    if (s_current_texture == this) {
        Texture<TType>::unbind_all();
    }
}

/*----------------------------------------------------------------------------*/

template class vq::graphics::core::Texture<TextureType::TEXTURE_1D>;
template class vq::graphics::core::Texture<TextureType::TEXTURE_2D>;
template class vq::graphics::core::Texture<TextureType::TEXTURE_3D>;
template class vq::graphics::core::Texture<TextureType::TEXTURE_CUBE_MAP>;

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::core
