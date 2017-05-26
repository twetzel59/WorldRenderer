#include <utility>
#include <cmath>
#include <glm/trigonometric.hpp>
#include "blockshader.hpp"
#include "camera.hpp"
#include "entity.hpp"
#include "model.hpp"
#include "texture.hpp"
#include "window.hpp"

int main(int argc, char **argv) {
    Window win(800, 600, "WorldRenderer");
    win.setVSync(true);

    glEnable(GL_CULL_FACE);

    BlockShader shader("block");

    Texture tex_old("tex");
    //Test that move ctor double free really is fixed.
    Texture tex = std::move(tex_old);

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
                        1.0f, 1.0f, 1.0f,
                        1.0f, 1.0f, 1.0f,
                        1.0f, 1.0f, 1.0f,
                        1.0f, 1.0f, 1.0f,
                    },

                    {
                        0.0f, 1.0f,
                        0.0f, 0.0f,
                        1.0f, 0.0f,
                        1.0f, 1.0f
                    },

                    tex

                    );

    //Test that move ctor double free really is fixed.
    Model model = std::move(model_old);

    std::pair<int, int> win_size = win.getSize();
    Camera cam((float) win_size.first / win_size.second);

    Entity entity(model, Transform(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec2(glm::radians(45.0f), 0.0f)));

    bool run = true;
    while(run) {

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.start();
        cam.update();
        shader.setProjection(cam.getProjectionMatrix());
        shader.setView(cam.getViewMatrix());

        entity.draw(shader);

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
