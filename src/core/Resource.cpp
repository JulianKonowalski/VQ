#include "vq/core/Resource.hpp"

namespace vq::core {

/*----------------------------------------------------------------------------*/

Resource::Resource(const std::string& id) : m_id(id), m_is_loaded(false) {}

/*----------------------------------------------------------------------------*/

Resource::Resource(Resource&& other) { *this = std::move(other); }

/*----------------------------------------------------------------------------*/

Resource& Resource::operator=(Resource&& other) {
    m_id        = std::move(other.m_id);
    m_is_loaded = other.m_is_loaded;
    return *this;
}

/*----------------------------------------------------------------------------*/

bool Resource::load() {
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

bool Resource::reload() {
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

void Resource::unload() {
    if (!m_is_loaded) {
        return;
    }

    this->do_unload();
    this->emit_event<ResourceUnloadEvent>(*this);
    m_is_loaded = false;
}

/*----------------------------------------------------------------------------*/

ResourceManager& ResourceManager::get_instance() {
    static ResourceManager resource_manager;
    return resource_manager;
}

/*----------------------------------------------------------------------------*/

} // namespace vq::core
