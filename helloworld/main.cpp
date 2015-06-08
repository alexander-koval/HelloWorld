#include <iostream>
#include <sstream>
#include <stb.h>
#include <execinfo.h>
#include <Grafit/Graphics/Shader.hpp>
#include <Grafit/Graphics/Triangle.hpp>
#include <Grafit/Graphics/Bitmap.hpp>
#include <Grafit/Window/Window.hpp>
#include <Grafit/System/Clock.hpp>
#include <Grafit/System/String.hpp>
#include <Grafit/System/SourceInfo.hpp>
#include <Grafit/System/Assert.hpp>
#include <Grafit/System/SystemInfo.hpp>
#include <Grafit/System/File.hpp>
#include <Grafit/Graphics/Sprite.hpp>
#include <Grafit/Graphics/Geometry/Rect.hpp>


static const int WIDTH = 1280;
static const int HEIGHT = 960;

gf::Bitmap* picture;
gf::Sprite* sprite;
gf::Triangle* triangle;
//Image* image;

#ifdef __APPLE__
const std::string filename = "../Resources/Lenna.png";
const std::string filename1 = "../Resources/serrano.png";
#else
const std::string filename = "Resources/Lenna.png";
const std::string filename1 = "Resources/serrano.png";
#endif

gf::Window* window = NULL;
Mat4F projection = Mat4F();
Mat4F modelView = Mat4F();
float rotation = 1.f;
float translation = .005f;
gf::Time statsTime = gf::Time::Zero;
Int32 statsFPS;

int frameCount;
double previousSeconds = 0;

using namespace std;

void on_terminate(void) {
    void* trace_elems[20];
    int trace_elem_count(backtrace(trace_elems, 20));
    char** stack_syms(backtrace_symbols(trace_elems, trace_elem_count));
    for (int i = 0; i < trace_elem_count; ++i) {
        std::cout << stack_syms[i] << "\n";
    }
    std::free(stack_syms);
    exit(1);
}

void init() {
//    image = new Image();
    picture = new gf::Bitmap(filename);
    picture->setOrigin(256, 256);
//    picture->setScale(2.0f, 2.0f);

    picture->setPosition(512, 512);
    gf::Texture* texture = new gf::Texture();
    texture->loadFromFile(filename1, gf::RectI(0, 0, 629, 794));
    sprite = new gf::Sprite(*texture/*, gf::RectI(0, 0, 512, 512)*/);
//    picture2->setOrigin(0.5, 0.5);
//    picture2->setScale(2.0f, 2.0f);
    sprite->setPosition(0, 0);
    triangle = new gf::Triangle();
    GF_ASSERT(false, "Test Call Return %d", 1);
}

void render() {
    window->clear(ColorU(180, 180, 180, 255));
//    window->clear(ColorU::Red);
//    window->clear(ColorF(0.7f, 0.7f, 0.7f, 1.f));
//    GL_CHECK(glClearColor(1.0f, 1.0f, 0.0f, 1.0f));
//    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
//    rotation += 0.1f;
//    tranlation += 0.01f;
//    modelView.rotate(rotation);
//    modelView.translate(translation, translation, 0);
    Mat4F mvpView = projection * modelView;
//    image->render(mvpView);
    triangle->render(mvpView);
//    picture->setScale(picture->getScale().x + 0.01f, picture->getScale().y + 0.01f);
//    picture->render(mvpView);0
//    picture2->render(mvpView);
//    sprite->setRotation(sprite->getRotation() + 1);
    window->draw(*picture);
    window->draw(*sprite);
    window->display();
}

void updateStatistics(gf::Time dt) {
    statsTime += dt;
    statsFPS += 1;
    if (statsTime >= gf::seconds(1.0f)) {
        std::ostringstream os;
        os << statsFPS;
        window->setTitle(os.str());
        statsTime -= gf::seconds(1.0f);
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
    std::set_terminate(on_terminate);
    window = new gf::Window(VideoMode(1024, 768), "Hello World", gf::Style::Default);
    window->setView(window->getDefaultView());
    if (gladLoadGL()) {
        std::cout << "\tVendor: " << glGetString (GL_VENDOR) << std::endl;
        std::cout << "\tRenderer: " << glGetString (GL_RENDERER) << std::endl;
        std::cout << "\tVersion: " << glGetString (GL_VERSION) << std::endl;
        std::cout << "\tGLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
        std::cout << "\tDPI: " << window->getDotsPerInch() << std::endl;
    }
    std::cout << "\tUSER_NAME: " << gf::SystemInfo::getUserName() << "\n"
              << "\tHOST_NAME: " << gf::SystemInfo::getHostName() << "\n"
              << "\t  APP_DIR: " << gf::SystemInfo::getApplicationDirectory() << "\n"
              << "\t USER_DIR: " << gf::SystemInfo::getUserDirectory() << "\n"
              << "\t TEMP_DIR: " << gf::SystemInfo::getTempDirectory() << "\n"
              << std::endl;

    gf::File file = gf::File(gf::SystemInfo::getApplicationDirectory() + "/Resources/Lenna.png");
    std::cout << "Name: " << file.getName().toAnsiString() << "\n"
              << " Ext: " << file.getExtension().toAnsiString() << "\n"
              << "Size: " << file.getSize() << std::endl;

    window->setVerticalSyncEnabled(true);
    init();
    gf::Clock clock;
    gf::Time lastTime = gf::Time::Zero;
    while (window->isOpen()) {
        gf::Time dt = clock.restart();
        lastTime += dt;
        updateFPS();
        render();
        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}
