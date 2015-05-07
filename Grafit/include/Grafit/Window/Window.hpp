#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <Grafit/System/Types.hpp>
#include <Grafit/Window/VideoMode.hpp>
#include <Grafit/Graphics/Geometry/Vector2.hpp>
#include <Grafit/Graphics/RenderTarget.hpp>

class GLFWwindow;

namespace gf {

namespace Style {
    enum {
        None       = 0,
        Titlebar   = 1 << 0,
        Resize     = 1 << 1,
        Close      = 1 << 2,
        Fullscreen = 1 << 3,

        Default = Titlebar | Resize | Close
    };
}

struct ContextSettings {
    explicit ContextSettings(unsigned int depth = 0, unsigned int stencil = 0, unsigned int antialiasing = 0, unsigned int major = 3, unsigned int minor = 3) :
    depthBits        (depth),
    stencilBits      (stencil),
    antialiasingLevel(antialiasing),
    majorVersion     (major),
    minorVersion     (minor)
    {
    }

    unsigned int depthBits;
    unsigned int stencilBits;
    unsigned int antialiasingLevel;
    unsigned int majorVersion;
    unsigned int minorVersion;
};

class Window : public RenderTarget {
public:
    Window(void);

    Window(VideoMode mode, const std::string& title, Uint32 style = Style::Default, const ContextSettings& settings = ContextSettings());

    ~Window(void);

    void create(VideoMode mode, const std::string& title, Uint32 style = Style::Default, const ContextSettings& settings = ContextSettings());

    void close(void);

    bool isOpen(void) const;

    const ContextSettings& getSettings(void) const;

    Vector2I getPosition(void) const;

    void setPosition(const Vector2I& position);

    virtual Vector2U getSize(void) const;

    double getDotsPerInch(void) const;

    void setSize(const Vector2U& size);

    void setTitle(const std::string& title);

    void setIcon(unsigned int width, unsigned int height, const Uint8* pixels);

    void setVisible(bool visible);

    void setVerticalSyncEnabled(bool enabled);

    void setMouseCursorVisible(bool visible);

    void setKeyRepeatEnabled(bool enabled);

    void setFramerateLimit(unsigned int limit);

    void setJoystickThreshold(float threshold);

    bool setActive(bool active = true) const;

    void requestFocus(void);

    bool hasFocus(void) const;

    void display(void);

private:
    void initialize(void);

    inline virtual bool activate(bool active) {
        return setActive(active);
    }

    GLFWwindow* m_window;
    GLFWwindow* m_previous;
};

}
#endif // WINDOW_HPP
