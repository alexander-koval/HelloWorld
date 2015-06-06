#ifndef IMAGEDATA_HPP
#define IMAGEDATA_HPP

#include <vector>
#include <Grafit/Graphics/Shader.hpp>
#include <Grafit/Graphics/OpenGL.hpp>
#include <Grafit/System/Types.hpp>

namespace gf {
class BitmapData {
public:
    BitmapData(void);

    ~BitmapData(void);

    bool loadFromFile(const std::string& filename);

    bool loadFromMemory(const void* data, std::size_t size);

    glm::vec2 getSize(void) const;

    const Uint8* getPixels() const;

    Int32 getNumChannels(void) const;

    void flipX(void);

    void flipY(void);

    bool isTransparent(void) const;

private:
    Int32 m_channels;
    glm::vec2 m_size;
    std::vector<Uint8> m_pixels;
};
}
#endif // IMAGEDATA_HPP
