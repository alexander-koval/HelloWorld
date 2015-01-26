#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <icebird/Graphics/Shader.hpp>
#include <icebird/Graphics/glm/glm.hpp>
#include <icebird/Graphics/glm/gtc/matrix_transform.hpp>
#include <icebird/Graphics/glm/gtc/type_ptr.hpp>

#define GL_CHECK(x) x; glCheckError(__FILE__, __LINE__);
#define STRINGIFY(x) #x

static const int WIDTH = 1280;
static const int HEIGHT = 960;

Shader shader;

GLuint vaoID;
GLuint vboVerticesID;
GLuint vboIndicesID;

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
};

Vertex vertices[3];
GLushort indices[3];

glm::mat4 projection = glm::mat4(1);
glm::mat4 modelView = glm::mat4(1);

using namespace std;
void glCheckError(const char* file, unsigned int line) {
    // Get the last error
    GLenum errorCode = glGetError();

    if (errorCode != GL_NO_ERROR) {
        std::string fileString(file);
        std::string error = "unknown error";
        std::string description  = "no description";

        // Decode the error code
        switch (errorCode) {
            case GL_INVALID_ENUM: {
                error = "GL_INVALID_ENUM";
                description = "an unacceptable value has been specified for an enumerated argument";
                break;
            }

            case GL_INVALID_VALUE: {
                error = "GL_INVALID_VALUE";
                description = "a numeric argument is out of range";
                break;
            }

            case GL_INVALID_OPERATION: {
                error = "GL_INVALID_OPERATION";
                description = "the specified operation is not allowed in the current state";
                break;
            }

            case GL_STACK_OVERFLOW: {
                error = "GL_STACK_OVERFLOW";
                description = "this command would cause a stack overflow";
                break;
            }

            case GL_STACK_UNDERFLOW: {
                error = "GL_STACK_UNDERFLOW";
                description = "this command would cause a stack underflow";
                break;
            }

            case GL_OUT_OF_MEMORY: {
                error = "GL_OUT_OF_MEMORY";
                description = "there is not enough memory left to execute the command";
                break;
            }
        }

        // Log the error
        std::cerr << "An internal OpenGL call failed in "
              << fileString.substr(fileString.find_last_of("\\/") + 1) << " (" << line << ") : "
              << error << ", " << description
              << std::endl;
    }
}

void init() {
    shader.loadFromFile("shaders/shaderpc.vert", Shader::VERTEX);
    shader.loadFromFile("shaders/shaderpc.frag", Shader::FRAGMENT);
    GL_CHECK(shader.createAndLinkProgram());
    GL_CHECK(shader.use());
    shader.addAttribute("a_vertex");
    shader.addAttribute("a_color");
    shader.addUniform("MVP");
    GL_CHECK(shader.unUse());

    vertices[0].color = glm::vec3(1, 0, 0);
    vertices[1].color = glm::vec3(0, 1, 0);
    vertices[2].color = glm::vec3(0, 0, 1);

    vertices[0].position = glm::vec3(-1, -1, 0);
    vertices[1].position = glm::vec3( 0,  1, 0);
    vertices[2].position = glm::vec3( 1, -1, 0);

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;

    GL_CHECK(glGenVertexArrays(1, &vaoID));
    GL_CHECK(glGenBuffers(1, &vboVerticesID));
    GL_CHECK(glGenBuffers(1, &vboIndicesID));
    GLsizei stride = sizeof(Vertex);

    GL_CHECK(glBindVertexArray(vaoID));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW));

    GL_CHECK(glEnableVertexAttribArray(shader["a_vertex"]));
    GL_CHECK(glVertexAttribPointer(shader["a_vertex"], 3, GL_FLOAT, GL_FALSE, stride, 0));

    GL_CHECK(glEnableVertexAttribArray(shader["a_color"]));
    GL_CHECK(glVertexAttribPointer(shader["a_color"], 3, GL_FLOAT, GL_FALSE, stride,
             (const GLvoid*)offsetof(Vertex, color)));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW));
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(GL_RED, 0, 0, 0);
    shader.use();
    GL_CHECK(glUniformMatrix4fv(shader("MVP"), 1, GL_FALSE,
                                glm::value_ptr(projection * modelView)));
    shader.unUse();
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
    GLenum err= glewInit();
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

