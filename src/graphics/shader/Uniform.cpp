#include "vq/graphics/shader/Uniform.hpp"

#include "vq/graphics/shader/Shader.hpp"

#include <glad/glad.h>
#include <glm/mat4x4.hpp>

namespace vq::graphics::shader {

/*----------------------------------------------------------------------------*/

template <typename ValueType>
Uniform<ValueType>::Uniform(const std::string& uniform_id,
                            unsigned int uniform_location)
    : m_uniform_id(uniform_id), m_uniform_location(uniform_location) {}

/*----------------------------------------------------------------------------*/

template <typename ValueType>
Uniform<ValueType>::Uniform(Uniform<ValueType>&& other)
    : EventHandler(std::move(other)),
      m_uniform_id(std::move(other.m_uniform_id)),
      m_uniform_location(other.m_uniform_location) {}

/*----------------------------------------------------------------------------*/

template <typename ValueType>
Uniform<ValueType>::Uniform(const Uniform<ValueType>& other)
    : EventHandler(other), m_uniform_id(other.m_uniform_id),
      m_uniform_location(other.m_uniform_location) {}

/*----------------------------------------------------------------------------*/

template <typename ValueType>
Uniform<ValueType>& Uniform<ValueType>::operator=(Uniform<ValueType>&& other) {
    m_uniform_id       = std::move(other.m_uniform_id);
    m_uniform_location = other.m_uniform_location;
    EventHandler::operator=(std::move(other));
    return *this;
}

/*----------------------------------------------------------------------------*/

template <typename ValueType>
Uniform<ValueType>&
Uniform<ValueType>::operator=(const Uniform<ValueType>& other) {
    m_uniform_id       = other.m_uniform_id;
    m_uniform_location = other.m_uniform_location;
    EventHandler::operator=(other);
    return *this;
}

/*----------------------------------------------------------------------------*/

template <typename ValueType>
void Uniform<ValueType>::handle(
    vq::core::resource::ResourceReloadEvent& event) noexcept {
    auto* p_shader =
        dynamic_cast<vq::graphics::shader::Shader*>(&event.resource);
    if (p_shader) {
        p_shader->update_uniform<ValueType>(*this);
    }
}

/*----------------------------------------------------------------------------*/

template <>
void Uniform<glm::mat4>::set_value(const glm::mat4& value) {
    glUniformMatrix4fv(m_uniform_location, 1, GL_FALSE, &value[0][0]);
}

/*----------------------------------------------------------------------------*/

template class vq::graphics::shader::Uniform<glm::mat4>;

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::shader
