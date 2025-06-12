#include <Grafit/System/Assert.hpp>
#include <Grafit/System/File.hpp>
#include <Grafit/System/IO/FileStream.hpp>
#include <Grafit/Graphics/Texture.hpp>

namespace gf {
template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::load(Identifier id, const gf::File& file) {
    if (file.isExist() && file.isRegularFile()) {
        std::unique_ptr<Resource> resource(new Resource());
        if (!resource->create(file)) {
            throw std::runtime_error("ResourceManager::load - Failed to Load " + file.getName());
        }
        insert(id, std::move(resource));
    }
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceManager<Resource, Identifier>::load(Identifier id, const gf::File& file, const Parameter& param) {
    if (file.isExist() && file.isRegularFile()) {
        std::unique_ptr<gf::Texture> resource(new gf::Texture());
        if (!resource->create(file, param)) {
            throw std::runtime_error("ResourceManager::load - Failed to Load " + file.getName());
        }
        insert(id, std::move(resource));
    }
}

template <typename Resource, typename Identifier>
Resource& ResourceManager<Resource, Identifier>::get(Identifier id) {
    auto found = m_resourceMap.find(id);
    GF_ASSERT(found != m_resourceMap.end(), "", "");
    return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceManager<Resource, Identifier>::get(Identifier id) const {
    auto found = m_resourceMap.find(id);
    GF_ASSERT(found != m_resourceMap.end(), "", "");
    return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::insert(Identifier id, std::unique_ptr<Resource> resource) {
    auto inserted = m_resourceMap.insert(std::make_pair(id, std::move(resource)));
    GF_ASSERT(inserted.second, "", "");
}

}
