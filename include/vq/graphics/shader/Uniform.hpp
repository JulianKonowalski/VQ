#pragma once

#include "vq/core/event/EventHandler.hpp"
#include "vq/core/resource/IResource.hpp"

namespace vq::graphics::shader {

/*----------------------------------------------------------------------------*/

template <typename ValueType>
class Uniform final : public vq::core::event::EventHandler<
                          vq::core::resource::ResourceReloadEvent> {

    friend class Shader;

  public:
    ~Uniform() = default;

    Uniform(Uniform<ValueType>&& other);
    Uniform(const Uniform<ValueType>& other);

    Uniform<ValueType>& operator=(Uniform<ValueType>&& other);
    Uniform<ValueType>& operator=(const Uniform<ValueType>& other);

    void
    handle(vq::core::resource::ResourceReloadEvent& event) noexcept override;
    void set_value(const ValueType& value);

  private:
    Uniform(const std::string& uniform_id, unsigned int uniform_location);

    std::string m_uniform_id;
    unsigned int m_uniform_location;
};

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::shader
