#include "vq/graphics/transform/ITransform.hpp"

namespace vq::graphics::transform {

/*----------------------------------------------------------------------------*/

ITransform::ITransform() : m_transform_matrix(1.0f), m_is_dirty(true) {}

/*----------------------------------------------------------------------------*/

ITransform::ITransform(ITransform&& other)
    : EventEmitter(std::move(other)),
      m_transform_matrix(std::move(other.m_transform_matrix)),
      m_is_dirty(other.m_is_dirty) {}

/*----------------------------------------------------------------------------*/

ITransform::ITransform(const ITransform& other)
    : EventEmitter(other), m_transform_matrix(other.m_transform_matrix),
      m_is_dirty(other.m_is_dirty) {}

/*----------------------------------------------------------------------------*/

ITransform& ITransform::operator=(ITransform&& other) {
    m_transform_matrix = std::move(other.m_transform_matrix);
    m_is_dirty         = other.m_is_dirty;
    EventEmitter::operator=(std::move(other));
    this->emit_event<TransformChangeEvent>(*this);
    return *this;
}

/*----------------------------------------------------------------------------*/

ITransform& ITransform::operator=(const ITransform& other) {
    m_transform_matrix = other.m_transform_matrix;
    m_is_dirty         = other.m_is_dirty;
    EventEmitter::operator=(other);
    this->emit_event<TransformChangeEvent>(*this);
    return *this;
}

/*----------------------------------------------------------------------------*/

void ITransform::reset_transform() {
    this->on_reset();
    m_transform_matrix = glm::mat4(1.0f);
    this->emit_event<TransformResetEvent>(*this);
    this->set_dirty();
}

/*----------------------------------------------------------------------------*/

void ITransform::update_transform_matrix() {
    if (m_is_dirty) {
        this->on_update();
        m_is_dirty = false;
        this->emit_event<TransformUpdateEvent>(*this);
    }
}

/*----------------------------------------------------------------------------*/

const glm::mat4& ITransform::get_transform_matrix() {
    this->update_transform_matrix();
    return m_transform_matrix;
}

/*----------------------------------------------------------------------------*/

void ITransform::set_dirty() {
    m_is_dirty = true;
    this->emit_event<TransformChangeEvent>(*this);
}

/*----------------------------------------------------------------------------*/

} // namespace vq::graphics::transform
