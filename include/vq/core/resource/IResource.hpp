#pragma once

#include "vq/core/TypeId.hpp"
#include "vq/core/event/EventEmitter.hpp"
#include "vq/core/event/IEvent.hpp"

#include <string>

namespace vq::core::resource {

/*----------------------------------------------------------------------------*/

class IResource;

struct ResourceLoadEvent : public event::IEvent {
    ResourceLoadEvent(IResource& resource) : resource(resource) {}
    IResource& resource;
};

struct ResourceReloadEvent : public event::IEvent {
    ResourceReloadEvent(IResource& resource) : resource(resource) {}
    IResource& resource;
};

struct ResourceUnloadEvent : public event::IEvent {
    ResourceUnloadEvent(IResource& resource) : resource(resource) {}
    IResource& resource;
};

/*----------------------------------------------------------------------------*/

class IResource
    : public event::EventEmitter<ResourceLoadEvent, ResourceReloadEvent,
                                 ResourceUnloadEvent> {
  public:
    explicit IResource(const std::string& id);
    virtual ~IResource() = default;

    IResource(IResource&& other);
    IResource& operator=(IResource&& other);

    IResource(const IResource&)            = delete;
    IResource& operator=(const IResource&) = delete;

    template <typename ChildType>
    static inline size_t get_type_id();

    inline bool is_loaded() const;
    inline const std::string& get_id() const;

    bool load();
    bool reload();
    void unload();

  protected:
    virtual bool do_load() noexcept   = 0;
    virtual bool do_reload() noexcept = 0;
    virtual void do_unload() noexcept = 0;

  private:
    std::string m_id;
    bool m_is_loaded;
};

/*----------------------------------------------------------------------------*/

template <typename ChildType>
inline size_t IResource::get_type_id() {
    return TypeId<IResource>::get_type_id<ChildType>();
}

inline bool IResource::is_loaded() const { return m_is_loaded; }

inline const std::string& IResource::get_id() const { return m_id; }

/*----------------------------------------------------------------------------*/

} // namespace vq::core::resource
