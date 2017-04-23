#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <vector>
#include <queue>
#include <utility>
//#include <exception>
#include <string>
//#include <GL/glew.h>
//#include <glad/include/glad/glad.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "dynamicexception.hpp"
#include "event.hpp"

class Window /* final */ {
    public:
        typedef std::pair<int, int> hint_element_type;
        typedef std::vector<hint_element_type> hints_type;
    private:
        class LibGLFWInitializer {
            public:
                LibGLFWInitializer();
                ~LibGLFWInitializer();

                static void errorCallback(int error, const char *description);
        };
        static const LibGLFWInitializer _glfw_initializer;

        class HintsInitializer {
            public:
                HintsInitializer();
        };
        friend class HintsInitializer;

        static hints_type default_hints;
        static HintsInitializer _hints_initializer;

        GLFWwindow *m_handle;
        std::queue<Event> m_queue;
    public:
        //

        class LibGLFWInitException : public core::DynamicException {
            public:
                LibGLFWInitException(const std::string &msg) : DynamicException(msg) {}
        };

        class LibGLFWErrorException : public core::DynamicException {
            public:
                LibGLFWErrorException(const std::string &msg) : DynamicException(msg) {}
        };

        class LibGLInitException : public core::DynamicException {
            public:
                LibGLInitException(const std::string &msg) : DynamicException(msg) {}
        };

        class WindowInitException : public core::DynamicException {
            public:
                WindowInitException(const std::string &msg) : DynamicException(msg) {}
        };

        class WindowIconException : public core::DynamicException {
            public:
                WindowIconException(const std::string &msg) : DynamicException(msg) {}
        };
        //

        /*
        struct ContextHints {
            int samples;
            int opengl_ver_major;
            int opengl_ver_minor;
            bool opengl_forward_compat;

        };
        */

        Window(unsigned width,
               unsigned height,
               const char *name,
               const hints_type &hints = default_hints,
               bool glew_experimental = true);
        ~Window();
        void makeContextCurrent();
        void setVSync(bool enable);
        void display();
        void postEvent(const Event &ev);
        bool pollEvent(Event &result);
        //
        bool isKeyPressed(int key);

        //

        /* inline */ void setCursorNormal();
        /* inline */ void setCursorDisabled();
        void getCursorPos(double &result_x, double &result_y);
        void setCursorPos(double x, double y);

        //
        void setIcon(const std::string &path);
        //

        inline static const hints_type & getDefaultHints() { return default_hints; }
        static void closeCallback(GLFWwindow *window);
        static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void sizeCallback(GLFWwindow *window, int width, int height);
};

#endif // WINDOW_H_INCLUDED
