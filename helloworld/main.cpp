#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <icebird/Graphics/Shader.hpp>
#include <icebird/Graphics/glm/glm.hpp>
#include <icebird/Graphics/glm/gtc/matrix_transform.hpp>
#include <icebird/Graphics/glm/gtc/type_ptr.hpp>
#include <icebird/Graphics/Shaders.hpp>
#include <icebird/Graphics/GL/OpenGL.hpp>
#include <icebird/Graphics/Triangle.hpp>

#define STRINGIFY(x) #x

static const int WIDTH = 1280;
static const int HEIGHT = 960;

Triangle* triangle;

glm::mat4 projection = glm::mat4(1);
glm::mat4 modelView = glm::mat4(1);

using namespace std;
void init() {
    triangle = new Triangle();
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.7, 0.7, 0.7, 0);
    glm::mat4 mvpView = projection * modelView;
    triangle->render(mvpView);
}

int main() {
    if (!glfwInit()) exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_OPENGL_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    string title = "HELLO WORLD";
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, title.c_str(), NULL, NULL);
    if(!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowSize(window, WIDTH, HEIGHT);

    glewExperimental = GL_TRUE;
    GLenum err = GL_CHECK(glewInit());
    if (GLEW_OK != err) {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
    } else {
        std::cout << "\tUsing glew " << glewGetString(GLEW_VERSION) << std::endl;
        std::cout << "\tVendor: " << glGetString (GL_VENDOR) << std::endl;
        std::cout << "\tRenderer: " << glGetString (GL_RENDERER) << std::endl;
        std::cout << "\tVersion: " << glGetString (GL_VERSION) << std::endl;
        std::cout << "\tGLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    }

    init();

    while (!glfwWindowShouldClose(window)) { 
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}

