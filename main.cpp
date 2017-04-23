#include "window.hpp"

int main(int argc, char **argv) {
    Window win(800, 600, "WorldRenderer");
    win.setVSync(true);

    bool run = true;
    while(run) {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        win.display();

        Event ev;
        while(win.pollEvent(ev)) {
            switch(ev.type) {
                case Event::EventType::Key:
                    if(ev.key_ev.key == GLFW_KEY_ESCAPE) {
                        run = false;
                    }
                    break;
                case Event::EventType::Close:
                    run = false;
                    break;
            }
        }
    }

    return 0;
}
