#include <Grafit/System/Assert.hpp>
#include <Grafit/System/File.hpp>
#include <Grafit/System/FileStream.hpp>
#include <Grafit/Graphics/Texture.hpp>

namespace gf {
template <typename Identifier>
void ResourceManager<gf::Texture, Identifier>::load(Identifier id, const gf::File& file) {
    if (file.isExist() && file.isRegularFile()) {
        gf::Image image;
        std::unique_ptr<gf::Texture> resource(new gf::Texture());
        gf::FileStream stream;
        stream.open(&file);
        image.load(stream);
        if (!resource->loadFromImage(image)) {
            throw std::runtime_error("ResourceManager::load - Failed to Load " + file.getName());
        }
        insert(id, std::move(resource));
    }
}

template <typename Identifier>
template <typename Parameter>
void ResourceManager<gf::Texture, Identifier>::load(Identifier id, const gf::File& file, const Parameter& param) {
    if (file.isExist() && file.isRegularFile()) {
        gf::Image image;
        std::unique_ptr<gf::Texture> resource(new gf::Texture());
        gf::FileStream stream;
        stream.open(&file);
        image.load(stream);
        if (!resource->loadFromImage(image, param)) {
            throw std::runtime_error("ResourceManager::load - Failed to Load " + file.getName());
        }
        insert(id, std::move(resource));
    }
}

template <typename Identifier>
gf::Texture& ResourceManager<gf::Texture, Identifier>::get(Identifier id) {
    auto found = m_resourceMap.find(id);
    GF_ASSERT(found != m_resourceMap.end(), "", "");
    return *found->second;
}

template <typename Identifier>
const gf::Texture& ResourceManager<gf::Texture, Identifier>::get(Identifier id) const {
    auto found = m_resourceMap.find(id);
    GF_ASSERT(found != m_resourceMap.end(), "", "");
    return *found->second;
}

template <typename Identifier>
void ResourceManager<gf::Texture, Identifier>::insert(Identifier id, std::unique_ptr<gf::Texture> resource) {
    auto inserted = m_resourceMap.insert(std::make_pair(id, std::move(resource)));
    GF_ASSERT(inserted.second, "", "");
}

}
