#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <Grafit/System/Types.hpp>
#include <Grafit/Graphics/Geometry/Rect.hpp>
#include <Grafit/Graphics/Geometry/Vector2.hpp>

namespace gf {
class Image;
class Texture {
public:
    static void bind(const Texture* texture);

    static Uint32 getMaximumSize(void);

    Texture(void);

    Texture(const Texture& copy);

    ~Texture(void);

    bool create(Uint32 width, Uint32 height);

    bool loadFromFile(const std::string filename, const RectI& area = RectI());

    bool loadFromMemory(const void* data, std::size_t size, const RectI& area = RectI());

    bool loadFromImage(const Image& image, const RectI& area = RectI());

    void update(const Uint8* pixels);

    void update(const Uint8* pixels, Uint32 width, Uint32 height, Uint32 x, Uint32 y);

    void update(const Image& image);

    void update(const Image& image, Uint32 x, Uint32 y);

    Vector2U getSize(void) const;

    void setSmooth(bool smooth);

    bool isSmooth(void) const;

    void setRepeated(bool repeated);

    bool isRepeated(void) const;

    Texture& operator =(const Texture& right);

private:
    static Uint32 getValidSize(Uint32 size);
    static bool  isPowerOfTwo(Uint32 size);
    static Uint32 getPowerOfTwo(Uint32 size);

    Vector2U m_size;
    Vector2U m_actualSize;
    Uint32 m_textureID;
    bool m_isSmooth;
    bool m_isRepeated;

//    template <typename Resource, typename Identifier>
//    friend class ResourceManager;
    friend class TextureLoader;
};
}
#endif // TEXTURE_HPP

