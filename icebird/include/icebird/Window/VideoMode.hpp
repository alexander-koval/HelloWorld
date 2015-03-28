#ifndef VIDEOMODE_HPP
#define VIDEOMODE_HPP

#include <vector>

class VideoMode {
public:
    static VideoMode getDesktopMode(void);

    static const std::vector<VideoMode>& getFullScreenModes(void);

    VideoMode(void);

    VideoMode(unsigned int width,
              unsigned int height,
              unsigned int redBits = 8,
              unsigned int greenBits = 8,
              unsigned int blueBits = 8);

    bool isValid(void) const;

    unsigned int width;
    unsigned int height;
    unsigned int redBits;
    unsigned int greenBits;
    unsigned int blueBits;
};

bool operator <(const VideoMode& left, const VideoMode& right);

bool operator >(const VideoMode& left, const VideoMode& right);

bool operator <=(const VideoMode& left, const VideoMode& right);

bool operator >=(const VideoMode& left, const VideoMode& right);

#endif // VIDEOMODE_HPP

