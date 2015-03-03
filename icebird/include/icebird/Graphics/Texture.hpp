#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <glm/vec2.hpp>
#include <icebird/System/Types.hpp>

class ImageData;
class Texture {
public:
    static void bind(const Texture& texture);

    static Uint32 getMaximumSize(void);

    Texture(void);

    Texture(const Texture& copy);

    ~Texture(void);

    bool initialize(Uint32 width, Uint32 height);

    bool loadFromFile(const std::string filename, const glm::vec2& area = glm::vec2());

    bool loadFromMemory(const void* data, std::size_t size, const glm::vec2& area = glm::vec2());

    bool loadFromImage(const ImageData& image, const glm::vec2& area);

    void update(const Uint8* pixels);

    void update(const Uint8* pixels, Uint32 width, Uint32 height, Uint32 x, Uint32 y);

    void update(const ImageData& image);

    void update(const ImageData& image, Uint32 x, Uint32 y);

    glm::vec2 getSize(void) const;

    void setSmooth(bool smooth);

    bool isSmooth(void) const;

    void setRepeated(bool repeated);

    bool isRepeated(void) const;

    Texture& operator =(const Texture& right);

private:
    static Int32 getValidSize(Int32 size);
    static bool isPowerOfTwo(Int32 size);
    static Int32 getPowerOfTwo(Int32 size);

    glm::vec2 m_size;
    glm::vec2 m_actualSize;
    Uint32 m_textureID;
    bool m_isSmooth;
    bool m_isRepeated;
};

#endif // TEXTURE_HPP

