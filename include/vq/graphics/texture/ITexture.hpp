#pragma once

#include "vq/core/resource/IResource.hpp"

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
class ITexture : public vq::core::resource::IResource {
  public:
    explicit ITexture(const std::string& id,
                      const std::vector<std::string>& source_files);
    ~ITexture() override = default;

    ITexture(ITexture<TType>&& other);
    ITexture<TType>& operator=(ITexture<TType>&& other);

    static void unbind_all();
    inline static ITexture<TType>* const get_current();
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
    static ITexture<TType>* s_current_texture;
};

/*----------------------------------------------------------------------------*/

template <TextureType TType>
ITexture<TType>* ITexture<TType>::s_current_texture = nullptr;

template <TextureType TType>
inline ITexture<TType>* const ITexture<TType>::get_current() {
    return s_current_texture;
}

template <TextureType TType>
inline constexpr TextureType ITexture<TType>::get_type() {
    return TType;
}

template <TextureType TType>
inline const std::vector<std::string>&
ITexture<TType>::get_source_files() const {
    return m_source_files;
}

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::texture
