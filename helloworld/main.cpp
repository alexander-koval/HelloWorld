#include <iostream>
#include <sstream>
#include <stb.h>
#include <memory>
#include <sys/wait.h>
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
#include <Grafit/System/FileStream.hpp>
#include <Grafit/Graphics/Sprite.hpp>
#include <Grafit/Graphics/Geometry/Rect.hpp>
#include <Grafit/System/Signals/Signal.hpp>
#include <Grafit/System/Signals/Slot.hpp>
#include <Grafit/System/ResourceManager.hpp>
#include <Grafit/System/Function.hpp>
#include <Grafit/System/Promise/EventLoop.hpp>
#include <Grafit/System/Promise/Deferred.hpp>
#include <Grafit/System/Promise/Promise.hpp>

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


gf::ResourceManager<gf::Texture, int> textureManager;

using namespace std;

void FreeFunction(int value) {
    std::cout << "FREE: " << value << std::endl;
}

void FreeFunction2(int value1) {
    std::cout << "FREE2: " << value1 << std::endl;
}

void on_terminate(void) {
//    void* trace_elems[20];
//    int trace_elem_count(backtrace(trace_elems, 20));
//    char** stack_syms(backtrace_symbols(trace_elems, trace_elem_count));
//    for (int i = 0; i < trace_elem_count; ++i) {
//        std::cout << stack_syms[i] << "\n";
//    }
//    std::free(stack_syms);
//    exit(EXIT_FAILURE);

    char pid_buf[30];
    sprintf(pid_buf, "%d", getpid());
    char name_buf[512];
    name_buf[readlink("/proc/self/exe", name_buf, 511)]=0;
    int child_pid = fork();
    if (!child_pid) {
        dup2(2,1); // redirect output to stderr
        fprintf(stdout,"stack trace for %s pid=%s\n",name_buf,pid_buf);
        execlp("gdb", "gdb", "--batch", "-n", "-ex", "thread", "-ex", "bt", name_buf, pid_buf, NULL);
        abort(); /* If gdb failed to start */
    } else {
        waitpid(child_pid,NULL,0);
    }
}

void init() {
//    image = new Image();
    picture = new gf::Bitmap(gf::SystemInfo::getApplicationDirectory() + gf::File::Separator + filename);
//    picture->setOrigin(256, 256);
//    picture->setScale(2.0f, 2.0f);

    picture->setPosition(512, 256);;
    gf::Texture& texture = textureManager.get(0);
    texture.setRepeated(true);
    sprite = new gf::Sprite(texture, gf::RectI(0, 0, 512, 512));
//    sprite->scale(0.4f, 0.6f);
//    sprite->setOrigin(sprite->getLocalBounds().width * 0.5,
//                      sprite->getLocalBounds().height * 0.5);
//    picture2->setOrigin(0.5, 0.5);
//    picture2->setScale(2.0f, 2.0f);
    sprite->setPosition(0, 0);
    triangle = new gf::Triangle();
//    gf::View view = window->getView();
//    view.setCenter(0.5, 0.5);
//    window->setView(view);
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
    if (elapsed_seconds > 0.5) {
        previousSeconds = current_seconds;
        char tmp[128];
        double fps = (double)frameCount / elapsed_seconds;
        sprintf(tmp, "opengl @ fps: %.2f", fps);
        window->setTitle(tmp);
        frameCount = 0;
    }
    frameCount++;
    gf::EventLoop::update(elapsed_seconds);
}

gf::Window* getWindow(gf::Window* window) {
    return window;
}

gf::Deferred<gf::Window*>::Ptr deferred;

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

    std::string dirPath(gf::SystemInfo::getApplicationDirectory());
    const std::string& filePath(dirPath.append(gf::File::Separator + filename1));
    gf::File file = gf::File(filePath);
    std::cout << "Name: " << file.getName().c_str() << "\n"
              << " Ext: " << file.getExtension().c_str() << "\n"
              << "Path: " << file.getNativePath() << "\n"
              << "Type: " << file.getType() << "\n"
              << "Size: " << file.getSize() << std::endl;
//    gf::FileStream* stream = new gf::FileStream(file);
//    stream->read();

    window->setVerticalSyncEnabled(true);

    std::shared_ptr<gf::Signal1<int>> signal = std::make_shared<gf::Signal1<int>>();
    gf::Connection& con1 = signal->connect(std::bind(&FreeFunction, std::placeholders::_1), true, 1);
    gf::Connection& con2 = signal->connect(std::bind(&FreeFunction2, std::placeholders::_1), false, 0);

    deferred = std::make_shared<gf::Deferred<gf::Window*>>();

//    std::function<gf::Window*(gf::Window*)> deff = getWindow;
//            [](gf::Window* window) -> gf::Window* {
//        int kkk = 1;
//        return window;
//    };
    gf::Promise<gf::Window*>::Ptr promise = deferred->promise()->then([](gf::Window* window) -> gf::Window* {
            int kkk = 1;
            std::cout << "PROMISE_1" << std::endl;
            return window;
    })->then([](gf::Window* window) -> gf::Window* {
            int kkk = 2;
            std::cout << "PROMISE_2" << std::endl;
            return window;
    });
//    gf::Promise<gf::Window*>::Ptr promise = deferred->promise()->then(deff);
    deferred->resolve(window);

//    std::cout << signal->numSlots() << std::endl;
//    signal->dispatch(4);
//    std::cout << con1.isConnected() << std::endl;
//    signal->disconnect(con1);
//    std::cout << signal->numSlots() << std::endl;
//    signal->dispatch(234);

//    gf::Signal<gf::Slot<void(*)(int)>, void(*)(int)> signal;
//    gf::Slot slot(signal, &FreeFunction);
//    gf::Slot<gf::Signal<Slot<void(*)(int)>, void(*)(int)>, void(*)(int)> slot;
//    signal.add(&FreeFunction);

    gf::Function<void()> func = gf::Function<void()>([]() {
        std::cout << "USER_NAME:" << std::endl;
    });
    func();
    textureManager.load(0, file);

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

