#include <algorithm>
#include "blockshader.hpp"
#include "model.hpp"
#include "window.hpp"

int main(int argc, char **argv) {
    Window win(800, 600, "WorldRenderer");
    win.setVSync(true);

    glEnable(GL_CULL_FACE);

    BlockShader shader("block.vert", "block.frag");

    Model model_old({
                        0, 2, 1,
                        0, 3, 2
                    },
                    {
                        -1.0f, -1.0f, 0.0f,
                        -1.0f, 1.0f, 0.0f,
                        1.0f, 1.0f, 0.0f,
                        1.0f, -1.0f, 0.0f
                    },
                    {
                        1.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 0.0f,
                    });

    //Test that move ctor double free really is fixed.
    Model model = std::move(model_old);

    bool run = true;
    while(run) {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.start();
        model.draw();
        shader.stop();

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
                default:
                    break;
            }
        }
    }

    return 0;
}
