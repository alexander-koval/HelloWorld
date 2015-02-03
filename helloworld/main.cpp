#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <SOIL.h>
#include <icebird/Graphics/Shader.hpp>
#include <icebird/Graphics/glm/glm.hpp>
#include <icebird/Graphics/glm/gtc/matrix_transform.hpp>
#include <icebird/Graphics/glm/gtc/type_ptr.hpp>
#include <icebird/Graphics/shaders/shaders.hpp>
#include <icebird/Graphics/GL/OpenGL.hpp>
#include <icebird/Graphics/Triangle.hpp>

#define STRINGIFY(x) #x

static const int WIDTH = 1280;
static const int HEIGHT = 960;

//Triangle* triangle;

Shader shader;

GLuint vaoID;
GLuint vboID[2];
GLuint textureID;

glm::vec2 vertices[4];
GLushort indices[6];

#ifdef __APPLE__
const std::string filename = "../Resources/Lenna.png";
#else
const std::string filename = "media/Lenna.png";
#endif

glm::mat4 projection = glm::mat4(1);
glm::mat4 modelView = glm::mat4(1);

using namespace std;
void init() {
//      triangle = new Triangle();

    printf("VERTEX: \n%s\n", positionTexture_vert.c_str());
    printf("FRAGMENT: \n%s\n", positionTexture_frag.c_str());

    shader.loadFromMemory(positionTexture_vert, Shader::VERTEX);
    shader.loadFromMemory(positionTexture_frag, Shader::FRAGMENT);
    GL_CHECK(shader.createAndLinkProgram());
    GL_CHECK(shader.use());
    GL_CHECK(shader.addParameter("VertexPosition", Shader::ATTRIBUTE));
    GL_CHECK(shader.addParameter("TextureMap", Shader::UNIFORM));
    GL_CHECK(shader.addParameter("MVP", Shader::UNIFORM));
    GL_CHECK(glUniform1i(shader.getParameter("TextureMap", Shader::UNIFORM), 0));
    GL_CHECK(shader.unUse());

    vertices[0] = glm::vec2(0.0, 0.0);
    vertices[1] = glm::vec2(1.0, 0.0);
    vertices[2] = glm::vec2(1.0, 1.0);
    vertices[3] = glm::vec2(0.0, 1.0);

    GLushort* id = &indices[0];
    id[0] = 0; id[1] = 1; id[2] = 2;
    id[3] = 0; id[4] = 2; id[5] = 3;

    GL_CHECK(glGenVertexArrays(1, &vaoID));
    GL_CHECK(glGenBuffers(1, &vboID[0]));
    GL_CHECK(glGenBuffers(1, &vboID[1]));
    GL_CHECK(glBindVertexArray(vaoID));

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vboID[0]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(shader.getParameter("VertexPosition", Shader::ATTRIBUTE)));
    GL_CHECK(glVertexAttribPointer(shader.getParameter("VertexPosition", Shader::ATTRIBUTE), 2, GL_FLOAT, GL_FALSE, 0, 0));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[1]));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW));

    int channels = 0;
    int texture_width = 0;
    int texture_height = 0;
    GLubyte* data = SOIL_load_image(filename.c_str(), &texture_width, &texture_height, &channels, SOIL_LOAD_AUTO);
    if (data == NULL) {
        std::cerr << "Cannot load image: " << filename.c_str() << std::endl;
        exit(EXIT_FAILURE);
    }
//    int x, y;
//    for (y = 0; (y * 2)  < texture_height; ++y) {
//        int index1 = y * texture_width * channels;
//        int index2 = (texture_height - 1 - y) * texture_width * channels;
//        for (x = texture_width * channels; x > 0; --x) {
//            GLubyte temp = data[index1];
//            data[index1] = data[index2];
//            data[index2] = temp;
//            ++index1;
//            ++index2;
//        }
//    }

    GL_CHECK(glGenTextures(1, &textureID));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));

    SOIL_free_image_data(data);

}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.7, 0.7, 0.7, 0);
    glm::mat4 mvpView = projection * modelView;
//    modelView = glm::scale(modelView, glm::vec3(2.0, 2.0, 1.0));
    shader.use();
    GL_CHECK(glUniformMatrix4fv(shader.getParameter("MVP", Shader::UNIFORM), 1, GL_FALSE, glm::value_ptr(mvpView)));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0));
    shader.unUse();
//    modelView = glm::scale(modelView, glm::vec3(0.5, 0.5, 1.0));
//    triangle->render(mvpView);
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

