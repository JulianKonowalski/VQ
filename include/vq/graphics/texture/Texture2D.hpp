#pragma once

#include "vq/graphics/texture/TextureBase.hpp"

namespace vq::graphics::texture {

/*----------------------------------------------------------------------------*/

class Texture2D final : public TextureBase<TextureType::TEXTURE_2D> {
  public:
    explicit Texture2D(const std::string& id, const std::string& source_file);
    ~Texture2D() = default;

    Texture2D(Texture2D&& other);
    Texture2D& operator=(Texture2D&& other);

  protected:
    bool do_load() noexcept override;
    bool do_reload() noexcept override;
    void do_unload() noexcept override;
};

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::texture
