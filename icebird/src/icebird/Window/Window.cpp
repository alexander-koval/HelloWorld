#include <icebird/Window/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <GLFW/glfw3.h>

namespace {
    const Window* fullscreenWindow = NULL;    
}

Window::Window(void)
    : m_window(NULL) {

}

Window::Window(VideoMode mode, const std::string &title, Uint32 style, const ContextSettings &settings)
    : m_window(NULL) {
    create(mode, title, style, settings);
}

Window::~Window(void) {
    glfwDestroyWindow(m_window);
    glfwTerminate();
    m_window = NULL;
}

void Window::create(VideoMode mode, const std::string &title, Uint32 style, const ContextSettings &settings) {
    close();
    if (!glfwInit()) exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_OPENGL_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, settings.majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, settings.minorVersion);
    glfwWindowHint(GLFW_RED_BITS, mode.redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode.greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode.blueBits);
    glfwWindowHint(GLFW_RESIZABLE, (style & Style::Resize) ? GL_TRUE : GL_FALSE);
    glfwWindowHint(GLFW_DECORATED, (style & Style::Titlebar) ? GL_TRUE : GL_FALSE);

    if (style & Style::Fullscreen) {
        if (fullscreenWindow) {
            std::cerr << "Creating two fullscreen windows is not allowed, switching to windowed mode" << std::endl;
            style &= ~Style::Fullscreen;
        }
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        m_window = glfwCreateWindow(mode.width, mode.height, title.c_str(), monitor, NULL);
    } else {
        if (!mode.isValid()) {
            std::cerr << "The requested video mode is not available, switching to a valid mode" << std::endl;
            mode = VideoMode::getFullScreenModes()[0];
        }
        fullscreenWindow = this;
        m_window = glfwCreateWindow(mode.width, mode.height, title.c_str(), NULL, NULL);
    }
    setActive();
}

void Window::close(void) {
    glfwSetWindowShouldClose(m_window, GL_TRUE);
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

}

void Window::setVisible(bool visible) {
    visible ? glfwShowWindow(m_window) : glfwHideWindow(m_window);
}

void Window::setVerticalSyncEnabled(bool enabled) {

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
    glfwMakeContextCurrent(m_window);
    return true;

}

void Window::requestFocus(void) {

}

bool Window::hasFocus(void) const {

}

void Window::display(void) {
    if (isOpen()) {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }
}
