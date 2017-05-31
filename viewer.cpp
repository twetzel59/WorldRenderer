#include "viewer.hpp"
#include <iostream>
#include <utility>
#include <cmath>
#include <glm/trigonometric.hpp>
#include "blockshader.hpp"
#include "chunk.hpp"
#include "entity.hpp"
#include "model.hpp"
#include "texture.hpp"

Viewer::Viewer()
    :   m_win(800, 600, "WorldRenderer"),
        m_cam((float) m_win.getSize().first / m_win.getSize().second)
{
    m_win.setVSync(true);

    run();
}

void Viewer::run() {

    BlockShader shader("block");

    Texture tex_old("grass");
    //Test that move ctor double free really is fixed.
    Texture tex = std::move(tex_old);

    /*
    Model model_old({
                        0,1,3,
                        3,1,2,
                        4,5,7,
                        7,5,6,
                        8,9,11,
                        11,9,10,
                        12,13,15,
                        15,13,14,
                        16,17,19,
                        19,17,18,
                        20,21,23,
                        23,21,22
                    },
                    {
                        -0.5f,0.5f,-0.5f,
                        -0.5f,-0.5f,-0.5f,
                        0.5f,-0.5f,-0.5f,
                        0.5f,0.5f,-0.5f,

                        -0.5f,0.5f,0.5f,
                        -0.5f,-0.5f,0.5f,
                        0.5f,-0.5f,0.5f,
                        0.5f,0.5f,0.5f,

                        0.5f,0.5f,-0.5f,
                        0.5f,-0.5f,-0.5f,
                        0.5f,-0.5f,0.5f,
                        0.5f,0.5f,0.5f,

                        -0.5f,0.5f,-0.5f,
                        -0.5f,-0.5f,-0.5f,
                        -0.5f,-0.5f,0.5f,
                        -0.5f,0.5f,0.5f,

                        -0.5f,0.5f,0.5f,
                        -0.5f,0.5f,-0.5f,
                        0.5f,0.5f,-0.5f,
                        0.5f,0.5f,0.5f,

                        -0.5f,-0.5f,0.5f,
                        -0.5f,-0.5f,-0.5f,
                        0.5f,-0.5f,-0.5f,
                        0.5f,-0.5f,0.5f
                    },

                    {
                        1.0f,1.0f,1.0f,
                        1.0f,1.0f,1.0f,
                        1.0f,1.0f,1.0f,

                        1.0f,1.0f,1.0f,
                        1.0f,1.0f,1.0f,
                        1.0f,1.0f,1.0f,

                        1.0f,1.0f,1.0f,
                        1.0f,1.0f,1.0f,
                        1.0f,1.0f,1.0f,

                        1.0f,1.0f,1.0f,
                        1.0f,1.0f,1.0f,
                        1.0f,1.0f,1.0f,

                        1.0f,1.0f,1.0f,
                        1.0f,1.0f,1.0f,
                        1.0f,1.0f,1.0f,

                        1.0f,1.0f,1.0f,
                        1.0f,1.0f,1.0f,
                        1.0f,1.0f,1.0f
                    },

                    {
                        0,0,
                        0,1,
                        1,1,
                        1,0,
                        0,0,
                        0,1,
                        1,1,
                        1,0,
                        0,0,
                        0,1,
                        1,1,
                        1,0,
                        0,0,
                        0,1,
                        1,1,
                        1,0,
                        0,0,
                        0,1,
                        1,1,
                        1,0,
                        0,0,
                        0,1,
                        1,1,
                        1,0
                    },

                    tex

                    );

    //Test that move ctor double free really is fixed.
    Model model = std::move(model_old);

    //Entity entity(model, Transform(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec2(glm::radians(45.0f), 0.0f)));
    Entity entity0(model, Transform(glm::vec3( 5.0f, -5.0f, -5.0f), glm::vec2(0.0f, 0.0f)));
    Entity entity1(model, Transform(glm::vec3( 5.0f, -5.0f,  5.0f), glm::vec2(0.0f, 0.0f)));
    Entity entity2(model, Transform(glm::vec3(-5.0f, -5.0f,  5.0f), glm::vec2(0.0f, 0.0f)));
    Entity entity3(model, Transform(glm::vec3(-5.0f, -5.0f, -5.0f), glm::vec2(0.0f, 0.0f)));
    Entity entity4(model, Transform(glm::vec3( 5.0f,  5.0f, -5.0f), glm::vec2(0.0f, 0.0f)));
    Entity entity5(model, Transform(glm::vec3( 5.0f,  5.0f,  5.0f), glm::vec2(0.0f, 0.0f)));
    Entity entity6(model, Transform(glm::vec3(-5.0f,  5.0f,  5.0f), glm::vec2(0.0f, 0.0f)));
    Entity entity7(model, Transform(glm::vec3(-5.0f,  5.0f, -5.0f), glm::vec2(0.0f, 0.0f)));
    */

    Chunk chunk(tex);

    m_cam.setTransform(Transform(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec2(0.0f, 0.0f)));

    m_win.setCursorDisabled();
    m_win.setCursorPos(0.0, 0.0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    bool run = true;
    while(run) {

        glClearColor(0.4f, 0.5f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.start();
        m_cam.update();
        shader.setProjection(m_cam.getProjectionMatrix());
        shader.setView(m_cam.getViewMatrix());

        chunk.draw(shader);

        /*
        entity0.draw(shader);
        entity1.draw(shader);
        entity2.draw(shader);
        entity3.draw(shader);
        entity4.draw(shader);
        entity5.draw(shader);
        entity6.draw(shader);
        entity7.draw(shader);
        */

        shader.stop();

        m_win.display();

        Event ev;
        while(m_win.pollEvent(ev)) {
            switch(ev.type) {
                case Event::EventType::Key:

                    switch(ev.key_ev.key) {
                        case GLFW_KEY_ESCAPE:
                            run = false;
                            break;
                        default:
                            break;
                    }

                    break;
                case Event::EventType::Close:
                    run = false;
                    break;
                case Event::EventType::Size:
                    glViewport(0, 0, ev.size_ev.width, ev.size_ev.height);
                    m_cam.viewportResize((float) ev.size_ev.width / ev.size_ev.height);
                    break;
                default:
                    break;
            }
        }

        handleKeys();
        handleMouse();
    }
}

void Viewer::handleKeys() {
    if(m_win.isKeyPressed(GLFW_KEY_SPACE)) {
        m_cam.moveY(0.08f);
    } else if(m_win.isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
        m_cam.moveY(-0.08f);
    }

    if(m_win.isKeyPressed(GLFW_KEY_W)) {
        m_cam.moveForward(-0.08f);
    } else if(m_win.isKeyPressed(GLFW_KEY_S)) {
        m_cam.moveForward(0.08f);
    }

    if(m_win.isKeyPressed(GLFW_KEY_A)) {
        m_cam.moveRight(-0.08f);
    } else if(m_win.isKeyPressed(GLFW_KEY_D)) {
        m_cam.moveRight(0.08f);
    }
}

void Viewer::handleMouse() {
    std::cout << "mouse: " << m_win.getCursorPos().first << " " << m_win.getCursorPos().second << std::endl;

    m_cam.rotateXY(m_win.getCursorPos().second / -200.0, m_win.getCursorPos().first / -200.0);

    m_win.setCursorPos(0.0, 0.0);
}
