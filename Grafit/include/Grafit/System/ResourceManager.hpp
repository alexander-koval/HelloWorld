#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include <string>
#include <memory>

namespace gf {
class File;
class Texture;
template <typename Resource, typename Identifier>
class ResourceManager {
public:
    void load(Identifier id, const gf::File& file);

    template <typename Parameter>
    void load(Identifier id, const gf::File& file, const Parameter& param);

    Resource& get(Identifier id);

    const Resource& get(Identifier id) const;

private:
    void insert(Identifier id, std::unique_ptr<Resource> resource);

private:
    std::map<Identifier, std::unique_ptr<Resource>> m_resourceMap;
};

}

#include <Grafit/System/ResourceManager.inl>
#endif // RESOURCEMANAGER_HPP
