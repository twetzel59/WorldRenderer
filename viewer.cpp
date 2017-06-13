#include "viewer.hpp"
#include <iostream>
#include <utility>
#include <cmath>
#include <glm/trigonometric.hpp>
#include "blockshader.hpp"
//#include "chunk.hpp"
#include "chunkmanager.hpp"
#include "clouds.hpp"
#include "cloudshader.hpp"
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

    BlockShader block_shader;
    CloudShader cloud_shader;

    Texture atlas_old("atlas");
    //Test that move ctor double free really is fixed.
    Texture atlas = std::move(atlas_old);

    ChunkManager cmgr(atlas);

    /** TODO: TEMPORARY **/
    Texture clouds_tex("clouds");
    glBindTexture(GL_TEXTURE_2D, clouds_tex.getId());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);

    Clouds clouds(clouds_tex);

    m_cam.setTransform(Transform(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec2(0.0f, 0.0f)));

    m_win.setCursorDisabled();
    m_win.setCursorPos(0.0, 0.0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    bool run = true;
    while(run) {

        m_day_night.update(m_win.getTime());
        DayNight::DayLight day = m_day_night.getDaylight();
        glm::vec3 sky_color = (glm::vec3(0.4f, 0.5f, 1.0f) +
                               (glm::vec3(0.8f, 0.2f, -0.4f) * day.goldenness)
                               ) * day.light;
        std::cout << "sky color: " << sky_color.x << ',' << sky_color.y << ',' << sky_color.z << std::endl;

        glClearColor(sky_color.x, sky_color.y, sky_color.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Blocks

        block_shader.start();

        m_cam.update();

        block_shader.setProjection(m_cam.getProjectionMatrix());
        block_shader.setView(m_cam.getViewMatrix());
        block_shader.setSkyColor(sky_color);
        block_shader.setDaylight(day.light);

        cmgr.draw(block_shader);

        block_shader.stop();

        //

        //Clouds

        cloud_shader.start();

        cloud_shader.setProjection(m_cam.getProjectionMatrix());
        cloud_shader.setView(m_cam.getViewMatrix());
        cloud_shader.setSkyColor(sky_color);
        cloud_shader.setDaylight(day.light);

        clouds.draw(cloud_shader);

        cloud_shader.stop();

        //

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
