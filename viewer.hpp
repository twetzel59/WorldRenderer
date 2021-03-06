#ifndef VIEWER_HPP_INCLUDED
#define VIEWER_HPP_INCLUDED

#include "camera.hpp"
#include "daynight.hpp"
#include "window.hpp"

class Viewer /* final */ {
    private:
        Window m_win;
        Camera m_cam;
        DayNight m_day_night;

        void run();
        void handleKeys();
        void handleMouse();
    public:
        Viewer();
        ~Viewer() {}

        Viewer(const Viewer &) = delete;
        Viewer & operator=(const Viewer &) = delete;
        Viewer(Viewer &&) = delete;
        Viewer & operator=(Viewer &&) = delete;
};

#endif // VIEWER_HPP_INCLUDED
