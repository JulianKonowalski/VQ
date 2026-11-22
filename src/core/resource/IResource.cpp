#include "vq/core/resource/IResource.hpp"

namespace vq::core::resource {

/*----------------------------------------------------------------------------*/

IResource::IResource(const std::string& id) : m_id(id), m_is_loaded(false) {}

/*----------------------------------------------------------------------------*/

IResource::IResource(IResource&& other) { *this = std::move(other); }

/*----------------------------------------------------------------------------*/

IResource& IResource::operator=(IResource&& other) {
    m_id        = std::move(other.m_id);
    m_is_loaded = other.m_is_loaded;
    return *this;
}

/*----------------------------------------------------------------------------*/

bool IResource::load() {
    if (m_is_loaded) {
        return true;
    }

    m_is_loaded = this->do_load();
    if (m_is_loaded) {
        this->emit_event<ResourceLoadEvent>(*this);
    }

    return m_is_loaded;
}

/*----------------------------------------------------------------------------*/

bool IResource::reload() {
    if (!m_is_loaded) {
        return false;
    }

    if (!this->do_reload()) {
        return false;
    }

    this->emit_event<ResourceReloadEvent>(*this);
    return true;
}

/*----------------------------------------------------------------------------*/

void IResource::unload() {
    if (!m_is_loaded) {
        return;
    }

    this->do_unload();
    this->emit_event<ResourceUnloadEvent>(*this);
    m_is_loaded = false;
}

/*----------------------------------------------------------------------------*/

} // namespace vq::core::resource
