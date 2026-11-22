#pragma once

#include "vq/graphics/texture/ITexture.hpp"

namespace vq::graphics::texture {

/*----------------------------------------------------------------------------*/

class TextureCubeMap final : public ITexture<TextureType::TEXTURE_CUBE_MAP> {
  public:
    explicit TextureCubeMap(const std::string& id,
                            const std::string& source_file_right,
                            const std::string& source_file_left,
                            const std::string& source_file_top,
                            const std::string& source_file_bottom,
                            const std::string& source_file_back,
                            const std::string& source_file_front);
    ~TextureCubeMap() = default;

    TextureCubeMap(TextureCubeMap&& other);
    TextureCubeMap& operator=(TextureCubeMap&& other);

  protected:
    bool do_load() noexcept override;
    bool do_reload() noexcept override;
    void do_unload() noexcept override;
};

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::texture
