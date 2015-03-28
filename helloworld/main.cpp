#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <SOIL.h>
#include <icebird/Graphics/Shader.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <icebird/Graphics/GL/OpenGL.hpp>
#include <icebird/Graphics/Triangle.hpp>
#include <icebird/Graphics/Image.hpp>
#include <icebird/Graphics/Texture.hpp>
#include <icebird/Graphics/Geometry/Mat4.hpp>
#include <icebird/Graphics/Image.hpp>
#include <icebird/Window/Window.hpp>
#include <icebird/Window/VideoMode.hpp>

#define STRINGIFY(x) #x

static const int WIDTH = 1280;
static const int HEIGHT = 960;

Image* picture;
Triangle* triangle;
//Image* image;

#ifdef __APPLE__
const std::string filename = "../Resources/Lenna.png";
#else
const std::string filename = "Resources/Lenna.png";
#endif

Mat4f projection = Mat4f();
Mat4f modelView = Mat4f();
float rotation = 1.f;
float translation = .005f;
using namespace std;

void init() {
//    image = new Image();
    picture = new Image();
    triangle = new Triangle();
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.7, 0.7, 0.7, 0.0);
//    rotation += 0.1f;
//    translation += 0.01f;
//    modelView.rotate(rotation);
//    modelView.translate(translation, translation, 0);
    Mat4f mvpView = projection * modelView;
//    image->render(mvpView);
    triangle->render(mvpView);
    picture->render(mvpView);
}

int main() {
    Window* window = new Window(VideoMode(1024, 768), "Hello World", Style::Default);

    if (gladLoadGL()) {
        std::cout << "\tDPI: " << window->getDotsPerInch() << std::endl;
        std::cout << "\tVendor: " << glGetString (GL_VENDOR) << std::endl;
        std::cout << "\tRenderer: " << glGetString (GL_RENDERER) << std::endl;
        std::cout << "\tVersion: " << glGetString (GL_VERSION) << std::endl;
        std::cout << "\tGLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    }

    init();

    while (window->isOpen()) {
        render();
        window->display();
    }

    return EXIT_SUCCESS;
}

