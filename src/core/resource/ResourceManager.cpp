#include "vq/core/resource/ResourceManager.hpp"

namespace vq::core::resource {

/*----------------------------------------------------------------------------*/

ResourceManager& ResourceManager::get_instance() {
    static ResourceManager resource_manager;
    return resource_manager;
}

/*----------------------------------------------------------------------------*/

} // namespace vq::core::resource
