#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <SOIL.h>
#include <Grafit/Graphics/Shader.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Grafit/Graphics/OpenGL.hpp>
#include <Grafit/Graphics/Triangle.hpp>
#include <Grafit/Graphics/Image.hpp>
#include <Grafit/Graphics/Texture.hpp>
#include <Grafit/Graphics/Geometry/Mat4.hpp>
#include <Grafit/Graphics/Image.hpp>
#include <Grafit/Window/Window.hpp>
#include <Grafit/Window/VideoMode.hpp>
#include <Grafit/System/Clock.hpp>
#include <Grafit/System/String.hpp>

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

gf::Window* window = NULL;
Mat4f projection = Mat4f();
Mat4f modelView = Mat4f();
float rotation = 1.f;
float translation = .005f;
Time statsTime = Time::Zero;
Int32 statsFPS;

int frameCount;
double previousSeconds = 0;

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
    modelView.rotate(rotation);
    modelView.translate(translation, translation, 0);
    Mat4f mvpView = projection * modelView;
//    image->render(mvpView);
    triangle->render(mvpView);
    picture->render(mvpView);
    window->display();
}

void updateStatistics(Time dt) {
    statsTime += dt;
    statsFPS += 1;
    if (statsTime >= seconds(1.0f)) {
        char tmp[128];
        sprintf(tmp, "opengl @ fps: %.2f", statsFPS);
        window->setTitle(tmp);
        statsTime -= seconds(1.0f);
        statsFPS = 0;
    }
}

void updateFPS() {
    double current_seconds;
    double elapsed_seconds;
    current_seconds = glfwGetTime();
    elapsed_seconds = current_seconds - previousSeconds;
    if (elapsed_seconds > 0.25) {
        previousSeconds = current_seconds;
        char tmp[128];
        double fps = (double)frameCount / elapsed_seconds;
        sprintf(tmp, "opengl @ fps: %.2f", fps);
        window->setTitle(tmp);
        frameCount = 0;
    }
    frameCount++;
}

int main() {
    window = new gf::Window(VideoMode(1024, 768), "Hello World", gf::Style::Default);

    if (gladLoadGL()) {
        std::cout << "\tVendor: " << glGetString (GL_VENDOR) << std::endl;
        std::cout << "\tRenderer: " << glGetString (GL_RENDERER) << std::endl;
        std::cout << "\tVersion: " << glGetString (GL_VERSION) << std::endl;
        std::cout << "\tGLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
        std::cout << "\tDPI: " << window->getDotsPerInch() << std::endl;
    }
    window->setVerticalSyncEnabled(true);
    init();
    Clock clock;
    Time lastTime = Time::Zero;
    while (window->isOpen()) {
        Time dt = clock.restart();
        lastTime += dt;
        updateFPS();
        render();
        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}

