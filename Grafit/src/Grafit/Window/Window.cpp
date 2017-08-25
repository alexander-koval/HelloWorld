#include <Grafit/Window/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace gf {
namespace {
    const Window* fullscreenWindow = nullptr;

    void onError(int error, const char* description) {
        std::cerr << "ERROR: " << error << " " << description << std::endl;
    }
}

Window::Window(void)
    : m_window(nullptr)
    , m_previous(nullptr) {

}

Window::Window(VideoMode mode, const std::string &title, Uint32 style, const ContextSettings &settings)
    : m_window(nullptr)
    , m_previous(nullptr) {
    if (!glfwInit()) exit(EXIT_FAILURE);
    glfwSetErrorCallback(onError);
    create(mode, title, style, settings);
}

Window::~Window(void) {
    close();
    glfwTerminate();
}

void Window::create(VideoMode mode, const std::string &title, Uint32 style, const ContextSettings &settings) {
    if (m_window) close();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, settings.majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, settings.minorVersion);
    glfwWindowHint(GLFW_RED_BITS, mode.redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode.greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode.blueBits);
    glfwWindowHint(GLFW_RESIZABLE, (style & Style::Resize) ? GL_TRUE : GL_FALSE);
    glfwWindowHint(GLFW_DECORATED, (style & Style::Titlebar) ? GL_TRUE : GL_FALSE);

    m_previous = glfwGetCurrentContext();
    if (style & Style::Fullscreen) {
        if (fullscreenWindow) {
            std::cerr << "Creating two fullscreen windows is not allowed, switching to windowed mode" << std::endl;
            m_window = glfwCreateWindow(mode.width, mode.height, title.c_str(), nullptr, nullptr);
        } else {
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            if (!mode.isValid()) {
                std::cerr << "The requested video mode is not available, switching to a valid mode" << std::endl;
                mode = VideoMode::getFullScreenModes()[0];
            }
            fullscreenWindow = this;
            m_window = glfwCreateWindow(mode.width, mode.height, title.c_str(), monitor, nullptr);
        }
    } else {
        m_window = glfwCreateWindow(mode.width, mode.height, title.c_str(), nullptr, nullptr);
    }
    initialize();
}

void Window::close(void) {
    glfwSetWindowShouldClose(m_window, GL_TRUE);
    glfwDestroyWindow(m_window);
    m_window = nullptr;
    fullscreenWindow = nullptr;
}

bool Window::isOpen(void) const {
    return m_window && !glfwWindowShouldClose(m_window);
}

const ContextSettings& Window::getSettings(void) const {
    static const ContextSettings empty(0, 0, 0);
    return empty;
}

Vector2I Window::getPosition(void) const {
    int xpos, ypos;
    glfwGetWindowPos(m_window, &xpos, &ypos);
    return Vector2I(xpos, ypos);
}

void Window::setPosition(const Vector2I &position) {
    glfwSetWindowPos(m_window, position.x, position.y);
}

double Window::getDotsPerInch(void) const {
    int widthMM, heightMM;
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwGetMonitorPhysicalSize(monitor, &widthMM, &heightMM);
    return mode->width / (widthMM / 25.4);
}

Vector2U Window::getSize(void) const {
    int width, height;
    glfwGetWindowSize(m_window, &width, &height);
    return Vector2U(width, height);
}

void Window::setSize(const Vector2U &size) {
    glfwSetWindowSize(m_window, size.x, size.y);
}

void Window::setTitle(const std::string &title) {
    glfwSetWindowTitle(m_window, title.c_str());
}

void Window::setIcon(unsigned int width, unsigned int height, const Uint8 *pixels) {
    //TODO Implement window icon
}

void Window::setVisible(bool visible) {
    visible ? glfwShowWindow(m_window) : glfwHideWindow(m_window);
}

void Window::setVerticalSyncEnabled(bool enabled) {
    if (setActive()) {
        glfwSwapInterval(enabled ? GL_TRUE : GL_FALSE);
    }
}

void Window::setMouseCursorVisible(bool visible) {

}

void Window::setKeyRepeatEnabled(bool enabled) {

}

void Window::setFramerateLimit(unsigned int limit) {

}

void Window::setJoystickThreshold(float threshold) {

}

bool Window::setActive(bool active) const {
    if (active) {
        glfwMakeContextCurrent(m_window);
        return true;
    } else {
        glfwMakeContextCurrent(m_previous);
        return false;
    }

}

void Window::requestFocus(void) {

}

bool Window::hasFocus(void) const {
    int focused = glfwGetWindowAttrib(m_window, GLFW_FOCUSED);
    return focused;
}

void Window::display(void) {
    if (setActive()) {
        glfwSwapBuffers(m_window);
    }
}

void Window::initialize(void) {
    RenderTarget::initialize();
    setVisible(true);
    setVerticalSyncEnabled(false);
    setActive();
}

}
