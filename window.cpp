#include "window.hpp"
#include <iostream>
#include <cstdlib>
#include <memory>
#include "lodepng/lodepng.h"

const Window::LibGLFWInitializer Window::_glfw_initializer;
Window::hints_type Window::default_hints;
Window::HintsInitializer Window::_hints_initializer;

Window::LibGLFWInitializer::LibGLFWInitializer() {
    glfwSetErrorCallback(errorCallback);

    if(!glfwInit()) {
        throw LibGLFWInitException("Failed to initialize GLFW!");
    }
}

void Window::LibGLFWInitializer::errorCallback(int error, const char *description) {
    throw LibGLFWErrorException(std::string("GLFW: ") + description);
}

Window::LibGLFWInitializer::~LibGLFWInitializer() {
    glfwTerminate();
}

Window::HintsInitializer::HintsInitializer() {
    Window::default_hints.push_back(Window::hint_element_type(GLFW_SAMPLES, 4));
    Window::default_hints.push_back(Window::hint_element_type(GLFW_CONTEXT_VERSION_MAJOR, 3));
    Window::default_hints.push_back(Window::hint_element_type(GLFW_CONTEXT_VERSION_MINOR, 3));
    Window::default_hints.push_back(Window::hint_element_type(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE));
    Window::default_hints.push_back(Window::hint_element_type(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));
}

Window::Window(unsigned width, unsigned height, const char *name, const hints_type &hints, bool glew_experimental) {
    /*
    if(!glfwInit()) {
        throw LibGLFWInitException("Failed to initialize GLFW!");
    }
    */

    /*
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    */

    m_handle = glfwCreateWindow(width, height, name, nullptr, nullptr);
    if(!m_handle) {
        throw WindowInitException("Failed to initialize OpenGL using GLEW!");
    }

    //glfwMakeContextCurrent(m_handle);
    makeContextCurrent();

    /*
    glewExperimental = (GLboolean)glew_experimental;
    if(glewInit() != GLEW_OK) {
        throw LibGLInitException("Failed to create GLFW window!");
    }
    */

    if(!gladLoadGL()) {
        throw LibGLInitException("Failed to initialize GLAD!");
    }
    printf("OpenGL Version %d.%d loaded\n", GLVersion.major, GLVersion.minor);

    /*
    for(const auto &i : default_hints) {
        std::cout << i.first << ", " << i.second << std::endl;
    }
    */
    glfwSetWindowUserPointer(m_handle, reinterpret_cast<void *>(this));
    glfwSetWindowCloseCallback(m_handle, closeCallback);
    glfwSetKeyCallback(m_handle, keyCallback);
    glfwSetWindowSizeCallback(m_handle, sizeCallback);
}

Window::~Window() {
    //glfwTerminate();
}

void Window::makeContextCurrent() {
    glfwMakeContextCurrent(m_handle);
}

void Window::setVSync(bool enable) {
    glfwSwapInterval((int)enable);
}

void Window::display() {
    glfwSwapBuffers(m_handle);
    glfwPollEvents();
}

void Window::postEvent(const Event &ev) {
    m_queue.push(ev);
}

bool Window::pollEvent(Event &result) {
    if(m_queue.size()) {
        result = m_queue.front();
        m_queue.pop();
        return true;
    }

    return false;
}

//

bool Window::isKeyPressed(int key) {
    return (glfwGetKey(m_handle, key) == GLFW_PRESS);
}

//

void Window::setCursorNormal() {
    glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::setCursorDisabled() {
    glfwSetInputMode(m_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

/*
void Window::getCursorPos(double &result_x, double &result_y) {
    glfwGetCursorPos(m_handle, &result_x, &result_y);
}
*/

void Window::setCursorPos(double x, double y) {
    glfwSetCursorPos(m_handle, x, y);
}

//

#include <unistd.h>
void Window::setIcon(const std::string &path) {
    std::vector<unsigned char> buf;

    unsigned width, height;
    unsigned err = lodepng::decode(buf, width, height, path);
    //for(auto i : buf) { std::cout << (unsigned int)i << std::endl; }

    if(err) {
        throw WindowIconException(std::string("Window::setIcon(): lodepng: ") + lodepng_error_text(err));
    }

    /*
    GLFWimage img;
    img.width = width;
    img.height = height;
    img.pixels = buf.data();
    */

    /*** FIX WITH C++14 std::make_unique ONCE C++14 IS SUPPORTED ON ALL TARGETS ***/
    auto img = std::unique_ptr<GLFWimage>(new GLFWimage);
    img->width = width;
    img->height = height;
    img->pixels = buf.data();
    std::cout << "pix : " << reinterpret_cast<void *>(img->pixels) << std::endl;

    glfwSetWindowIcon(m_handle, 1, img.get());
    sleep(0.3);
}

//

void Window::closeCallback(GLFWwindow *window) {
    reinterpret_cast<Window *>(glfwGetWindowUserPointer(window))->
        postEvent(
                  Event{
                        Event::EventType::Close,
                  }
        );
}

void Window::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    Event ev;

    ev.type = Event::EventType::Key;

    ev.key_ev.key = key;
    ev.key_ev.scancode = scancode;
    ev.key_ev.action = action;
    ev.key_ev.mods = mods;

    reinterpret_cast<Window *>(glfwGetWindowUserPointer(window))->postEvent(ev);

    /*
    reinterpret_cast<Window *>(glfwGetWindowUserPointer(window))->
        postEvent(
                  Event{
                        Event::EventType::Key,
                        Event::KeyEvent{key, scancode, action, mods}
                  }
        );

    */
    //glfwSetWindowPos(window, 100 + scancode, 100);
}

void Window::sizeCallback(GLFWwindow *window, int width, int height) {
    Event ev;

    ev.type = Event::EventType::Size;

    ev.size_ev.width = width;
    ev.size_ev.height = height;

    reinterpret_cast<Window *>(glfwGetWindowUserPointer(window))->postEvent(ev);

    /*
    reinterpret_cast<Window *>(glfwGetWindowUserPointer(window))->
        postEvent(
                  Event{
                        Event::EventType::Size,
                        Event::SizeEvent{width, height}
                  }
        );
    */
}
