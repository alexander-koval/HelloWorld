#ifndef IMAGEDATA_HPP
#define IMAGEDATA_HPP

#include <vector>
#include <Grafit/Graphics/Shader.hpp>
#include <Grafit/Graphics/OpenGL.hpp>
#include <Grafit/System/Types.hpp>

namespace gf {
class File;
class IInputStream;
class Image {
public:
    Image(void);

    ~Image(void);

    bool create(const gf::File& file);

    bool create(gf::IInputStream& stream);

    bool create(const Uint8* buffer, std::size_t size);

    Vector2U getSize(void) const;

    const Uint8* getPixels() const;

    Int32 getNumChannels(void) const;

    void flipX(void);

    void flipY(void);

    bool isTransparent(void) const;

private:
    Int32 m_channels;
    Vector2U m_size;
    std::vector<Uint8> m_pixels;
};
}
#endif // IMAGEDATA_HPP
