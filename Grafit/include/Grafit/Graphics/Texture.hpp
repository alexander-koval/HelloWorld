#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <Grafit/System/Types.hpp>
#include <Grafit/Graphics/Geometry/Rect.hpp>
#include <Grafit/Graphics/Geometry/Vector2.hpp>

namespace gf {
class BitmapData;
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

    bool loadFromImage(const BitmapData& image, const RectI& area = RectI());

    void update(const Uint8* pixels);

    void update(const Uint8* pixels, Uint32 width, Uint32 height, Uint32 x, Uint32 y);

    void update(const BitmapData& image);

    void update(const BitmapData& image, Uint32 x, Uint32 y);

    Vector2U getSize(void) const;

    void setSmooth(bool smooth);

    bool isSmooth(void) const;

    void setRepeated(bool repeated);

    bool isRepeated(void) const;

    Texture& operator =(const Texture& right);

private:
    static Int32 getValidSize(Int32 size);
    static bool  isPowerOfTwo(Int32 size);
    static Int32 getPowerOfTwo(Int32 size);

    Vector2U m_size;
    Vector2U m_actualSize;
    Uint32 m_textureID;
    bool m_isSmooth;
    bool m_isRepeated;
};
}
#endif // TEXTURE_HPP

