#include <icebird/Window/VideoMode.hpp>
#include <algorithm>
#include <functional>
#include <GLFW/glfw3.h>

VideoMode VideoMode::getDesktopMode(void) {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    return VideoMode(mode->width, mode->height, mode->redBits, mode->greenBits, mode->redBits);
}

const std::vector<VideoMode>& VideoMode::getFullScreenModes(void) {
    static std::vector<VideoMode> modes;
    if (modes.empty()) {
        int count;
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* vidmodes = glfwGetVideoModes(monitor, &count);
        modes.resize(count);
        for (int i = 0; i < count; i++) {
            const GLFWvidmode* vidmode = (vidmodes + i);
            modes[i] = VideoMode(vidmode->width,
                                 vidmode->height,
                                 vidmode->redBits,
                                 vidmode->greenBits,
                                 vidmode->blueBits);
        }
        std::sort(modes.begin(), modes.end(), std::greater<VideoMode>());
    }
    return modes;
}

VideoMode::VideoMode(void)
    : width(0)
    , height(0)
    , redBits(0)
    , greenBits(0)
    , blueBits(0) {

}

VideoMode::VideoMode(unsigned int width,
                     unsigned int height,
                     unsigned int redBits,
                     unsigned int greenBits,
                     unsigned int blueBits)
    : width(width)
    , height(height)
    , redBits(redBits)
    , greenBits(greenBits)
    , blueBits(blueBits) {

}


bool VideoMode::isValid(void) const {
    const std::vector<VideoMode>& modes = VideoMode::getFullScreenModes();
    return std::find(modes.begin(), modes.end(), *this) != modes.end();
}

bool operator ==(const VideoMode& left, const VideoMode& right) {
    return (left.width        == right.width)   &&
           (left.height       == right.height)  &&
           (left.redBits == right.redBits)      &&
           (left.greenBits == right.greenBits)  &&
           (left.blueBits == right.blueBits);
}


bool operator !=(const VideoMode& left, const VideoMode& right) {
    return !(left == right);
}


bool operator <(const VideoMode& left, const VideoMode& right) {
    unsigned int leftBits = left.redBits + left.greenBits + left.blueBits;
    unsigned int rightBits = right.redBits + right.greenBits + right.blueBits;
    if (leftBits == rightBits) {
        if (left.width == right.width) {
            return left.height < right.height;
        }
        else {
            return left.width < right.width;
        }
    }
    else {
        return leftBits < rightBits;
    }
}

bool operator >(const VideoMode& left, const VideoMode& right) {
    return right < left;
}

bool operator <=(const VideoMode& left, const VideoMode& right) {
    return !(right < left);
}

bool operator >=(const VideoMode& left, const VideoMode& right) {
    return !(left < right);
}
