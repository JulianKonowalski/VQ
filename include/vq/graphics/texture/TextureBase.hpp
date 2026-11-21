#pragma once

#include "vq/core/Resource.hpp"

#include <vector>

namespace vq::graphics::texture {

/*----------------------------------------------------------------------------*/

enum class TextureType { TEXTURE_1D, TEXTURE_2D, TEXTURE_3D, TEXTURE_CUBE_MAP };

enum class TextureWrapType {
    REPEAT,
    MIRROR_REPEAT,
    CLAMP_TO_EDGE,
    MIRROR_CLAMP_TO_EDGE,
    CLAMP_TO_BORDER
};

enum class TextureFilterType { NEAREST, LINEAR };

/*----------------------------------------------------------------------------*/

template <TextureType TType>
class TextureBase : public vq::core::Resource {
  public:
    explicit TextureBase(const std::string& id,
                         const std::vector<std::string>& source_files);
    ~TextureBase() override = default;

    TextureBase(TextureBase<TType>&& other);
    TextureBase<TType>& operator=(TextureBase<TType>&& other);

    static void unbind_all();
    inline static TextureBase<TType>* const get_current();
    inline static constexpr TextureType get_type();

    inline const std::vector<std::string>& get_source_files() const;

    void set_wrap_s(const TextureWrapType wrap_type);
    void set_wrap_t(const TextureWrapType wrap_type);
    void set_wrap_r(const TextureWrapType wrap_type);

    void set_filter_min(const TextureFilterType filter_type);
    void set_filter_mag(const TextureFilterType filter_type);

    void bind();
    void unbind();

  protected:
    std::vector<std::string> m_source_files;
    unsigned int m_texture_id;

  private:
    static TextureBase<TType>* s_current_texture;
};

/*----------------------------------------------------------------------------*/

template <TextureType TType>
TextureBase<TType>* TextureBase<TType>::s_current_texture = nullptr;

template <TextureType TType>
inline TextureBase<TType>* const TextureBase<TType>::get_current() {
    return s_current_texture;
}

template <TextureType TType>
inline constexpr TextureType TextureBase<TType>::get_type() {
    return TType;
}

template <TextureType TType>
inline const std::vector<std::string>&
TextureBase<TType>::get_source_files() const {
    return m_source_files;
}

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::texture
