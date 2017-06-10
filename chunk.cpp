#include "chunk.hpp"
#include "glm/vec3.hpp"
#include "transform.hpp"
#include <cstdlib>

Chunk::Chunk()
    :   m_model(nullptr),
        m_entity(nullptr)
{
    m_blocks.fill(Node(BlockId::Air));

    /*
    for(int x = 0; x < k_chunk_size; ++x) {
        for(int y = k_chunk_size - 2; y < k_chunk_size; ++y) {
            for(int z = 0; z < k_chunk_size; ++z) {
                if(y == k_chunk_size - 1 || rand() % 2) {
                    blockAt(x, y, z) = BlockId::Grass;
                }
            }
        }
    }
    */

    /*
    m_model = new Model(
        {
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

        uv
    );
    */

}

Chunk::~Chunk() {
    delete m_model;
    delete m_entity;
}

int Chunk::index(int x, int y, int z) const {
    return x + y * k_chunk_size + z * k_chunk_size_sq;
}

Node & Chunk::blockAt(int x, int y, int z) {
    return m_blocks.at(index(x, y, z));
}

const Node & Chunk::blockAt(int x, int y, int z) const {
    return m_blocks.at(index(x, y, z));
}

void Chunk::generateGeometry(const Texture &tex, int chunk_x, int chunk_y, int chunk_z) {
    delete m_model;
    m_model = nullptr;
    delete m_entity;
    m_entity = nullptr;

    std::vector<GLuint> indices;
    std::vector<GLfloat> positions;
    std::vector<GLfloat> colors;
    std::vector<GLfloat> uv;

    GLuint index = 0;
    for(int x = 0; x < k_chunk_size; ++x) {
        for(int y = 0; y < k_chunk_size; ++y) {
            for(int z = 0; z < k_chunk_size; ++z) {
                if(blockAt(x, y, z).getId() != BlockId::Air) {
                    //std::cout << "test" << std::endl;

                    //Redundant
                    /*
                    if(!blockAt(x, y, z).getId()) {
                        continue;
                    }
                    */

                    bool draw_front = true;
                    bool draw_back = true;
                    bool draw_top = true;
                    bool draw_bottom = true;
                    bool draw_right = true;
                    bool draw_left = true;

                    /*
                    if(x < k_chunk_size - 1) {
                        if(blockAt(x + 1, y, z).getId()) {
                            draw_right = false;
                        }
                    }
                    */

                    if((z < k_chunk_size - 1) && blockAt(x, y, z + 1).getId() != BlockId::Air) {
                        draw_front = false;
                        //std::cout << "noooo" << std::endl;
                    }

                    if((z > 0) && blockAt(x, y, z - 1).getId() != BlockId::Air) {
                        draw_back = false;
                    }

                    if((y < k_chunk_size - 1) && blockAt(x, y + 1, z).getId() != BlockId::Air) {
                        draw_top = false;
                    }

                    if((y > 0) && blockAt(x, y - 1, z).getId() != BlockId::Air) {
                        draw_bottom = false;
                    }

                    if((x < k_chunk_size - 1) && blockAt(x + 1, y, z).getId() != BlockId::Air) {
                        draw_right = false;
                    }

                    if((x > 0) && blockAt(x - 1, y, z).getId() != BlockId::Air) {
                        draw_left = false;
                    }

                    static constexpr GLfloat node_size = 1.0f;
                    const GLfloat x1 = node_size * x;
                    const GLfloat x2 = x1 + node_size;
                    const GLfloat y1 = node_size * y;
                    const GLfloat y2 = y1 + node_size;
                    const GLfloat z1 = node_size * z;
                    const GLfloat z2 = z1 + node_size;

                    //const GLfloat tex_w = ;
                    //const GLfloat tex_h = ;

                    const GLfloat u1 = ((GLfloat)(static_cast<int>(blockAt(x, y, z).getId()) - 1)) / k_block_id_max;
                    //std::cout << "\n\n\nu1: " << u1 << "\n\n\n" << std::endl;
                    const GLfloat u2 = u1 + (1.0f / k_block_id_max);
                    const GLfloat v1 = 0.0f;
                    const GLfloat v2 = 1.0f;

                    //const Node::id_type id = blockAt(x, y, z).getId();
                    //const GLfloat u1 = id * 0.5f;


                    //Front
                    if(draw_front) {
                        positions.push_back(x2);
                        positions.push_back(y2);
                        positions.push_back(z2);

                        positions.push_back(x1);
                        positions.push_back(y2);
                        positions.push_back(z2);

                        positions.push_back(x1);
                        positions.push_back(y1);
                        positions.push_back(z2);

                        positions.push_back(x2);
                        positions.push_back(y1);
                        positions.push_back(z2);


                        uv.push_back(u2);
                        uv.push_back(v1);

                        uv.push_back(u1);
                        uv.push_back(v1);

                        uv.push_back(u1);
                        uv.push_back(v2);

                        uv.push_back(u2);
                        uv.push_back(v2);


                        static constexpr GLfloat brightness = 0.92f;

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);


                        indices.push_back(index);
                        indices.push_back(index + 1);
                        indices.push_back(index + 2);

                        indices.push_back(index + 2);
                        indices.push_back(index + 3);
                        indices.push_back(index);


                        index += 4;
                    }
                    //


                    //Back
                    if(draw_back) {
                        positions.push_back(x1);
                        positions.push_back(y2);
                        positions.push_back(z1);

                        positions.push_back(x2);
                        positions.push_back(y2);
                        positions.push_back(z1);

                        positions.push_back(x2);
                        positions.push_back(y1);
                        positions.push_back(z1);

                        positions.push_back(x1);
                        positions.push_back(y1);
                        positions.push_back(z1);


                        uv.push_back(u2);
                        uv.push_back(v1);

                        uv.push_back(u1);
                        uv.push_back(v1);

                        uv.push_back(u1);
                        uv.push_back(v2);

                        uv.push_back(u2);
                        uv.push_back(v2);


                        static constexpr GLfloat brightness = 0.5f;

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);


                        indices.push_back(index);
                        indices.push_back(index + 1);
                        indices.push_back(index + 2);

                        indices.push_back(index + 2);
                        indices.push_back(index + 3);
                        indices.push_back(index);


                        index += 4;
                    }
                    //


                    //Top
                    if(draw_top) {
                        positions.push_back(x2);
                        positions.push_back(y2);
                        positions.push_back(z1);

                        positions.push_back(x1);
                        positions.push_back(y2);
                        positions.push_back(z1);

                        positions.push_back(x1);
                        positions.push_back(y2);
                        positions.push_back(z2);

                        positions.push_back(x2);
                        positions.push_back(y2);
                        positions.push_back(z2);


                        uv.push_back(u2);
                        uv.push_back(v1);

                        uv.push_back(u1);
                        uv.push_back(v1);

                        uv.push_back(u1);
                        uv.push_back(v2);

                        uv.push_back(u2);
                        uv.push_back(v2);


                        static constexpr GLfloat brightness = 1.0f;

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);


                        indices.push_back(index);
                        indices.push_back(index + 1);
                        indices.push_back(index + 2);

                        indices.push_back(index + 2);
                        indices.push_back(index + 3);
                        indices.push_back(index);


                        index += 4;
                    }
                    //


                    //Bottom
                    if(draw_bottom) {
                        positions.push_back(x2);
                        positions.push_back(y1);
                        positions.push_back(z2);

                        positions.push_back(x1);
                        positions.push_back(y1);
                        positions.push_back(z2);

                        positions.push_back(x1);
                        positions.push_back(y1);
                        positions.push_back(z1);

                        positions.push_back(x2);
                        positions.push_back(y1);
                        positions.push_back(z1);


                        uv.push_back(u2);
                        uv.push_back(v1);

                        uv.push_back(u1);
                        uv.push_back(v1);

                        uv.push_back(u1);
                        uv.push_back(v2);

                        uv.push_back(u2);
                        uv.push_back(v2);


                        static constexpr GLfloat brightness = 0.34f;

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);


                        indices.push_back(index);
                        indices.push_back(index + 1);
                        indices.push_back(index + 2);

                        indices.push_back(index + 2);
                        indices.push_back(index + 3);
                        indices.push_back(index);


                        index += 4;
                    }
                    //


                    //Left
                    if(draw_left) {
                        positions.push_back(x1);
                        positions.push_back(y2);
                        positions.push_back(z2);

                        positions.push_back(x1);
                        positions.push_back(y2);
                        positions.push_back(z1);

                        positions.push_back(x1);
                        positions.push_back(y1);
                        positions.push_back(z1);

                        positions.push_back(x1);
                        positions.push_back(y1);
                        positions.push_back(z2);


                        uv.push_back(u2);
                        uv.push_back(v1);

                        uv.push_back(u1);
                        uv.push_back(v1);

                        uv.push_back(u1);
                        uv.push_back(v2);

                        uv.push_back(u2);
                        uv.push_back(v2);


                        static constexpr GLfloat brightness = 0.67f;

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);


                        indices.push_back(index);
                        indices.push_back(index + 1);
                        indices.push_back(index + 2);

                        indices.push_back(index + 2);
                        indices.push_back(index + 3);
                        indices.push_back(index);


                        index += 4;
                    }
                    //


                    //Right
                    if(draw_right) {
                        positions.push_back(x2);
                        positions.push_back(y2);
                        positions.push_back(z1);

                        positions.push_back(x2);
                        positions.push_back(y2);
                        positions.push_back(z2);

                        positions.push_back(x2);
                        positions.push_back(y1);
                        positions.push_back(z2);

                        positions.push_back(x2);
                        positions.push_back(y1);
                        positions.push_back(z1);


                        uv.push_back(u2);
                        uv.push_back(v1);

                        uv.push_back(u1);
                        uv.push_back(v1);

                        uv.push_back(u1);
                        uv.push_back(v2);

                        uv.push_back(u2);
                        uv.push_back(v2);


                        /** WHICH IS BETTER?? ADJUSTED FOR VISUAL APPEARANCE. **/
                        //static constexpr GLfloat brightness = 0.84f;
                        static constexpr GLfloat brightness = 0.74f;

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);

                        colors.push_back(brightness);
                        colors.push_back(brightness);
                        colors.push_back(brightness);


                        indices.push_back(index);
                        indices.push_back(index + 1);
                        indices.push_back(index + 2);

                        indices.push_back(index + 2);
                        indices.push_back(index + 3);
                        indices.push_back(index);


                        index += 4;
                    }
                    //
                }
            }
        }
    }

    m_model = new Model(indices, positions, colors, uv, tex);

    m_entity = new Entity(*m_model, Transform(glm::vec3(
                                                        k_chunk_size * chunk_x,
                                                        k_chunk_size * chunk_y,
                                                        k_chunk_size * chunk_z), glm::vec3(0.0f, 0.0f, 0.0f)));
}

/*
void Chunk::generateGeometry(std::vector<GLuint> &indices,
                             std::vector<GLfloat> &positions,
                             std::vector<GLfloat> &colors,
                             std::vector<GLfloat> &uv) {

    static const glm::vec3 cube_pos[] = {
            {1.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            {1.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, 1.0f},
            {1.0f, 1.0f, 1.0f},
            {0.0f, 1.0f, 1.0f},
            {1.0f, 0.0f, 1.0f},
    };

    static const glm::vec3 cube_colors[] = {
            {1.0f, 1.0f, 1.0f},
            {1.0f, 1.0f, 1.0f},
            {1.0f, 1.0f, 1.0f},
            {1.0f, 1.0f, 1.0f},
            {1.0f, 1.0f, 1.0f},
            {1.0f, 1.0f, 1.0f}
    };

    static const glm::vec2 cube_uv[] = {
            {0.0f, 0.0f},
            {0.0f, 0.0f},
            {0.0f, 0.0f},
            {0.0f, 0.0f},
            {0.0f, 0.0f},
            {0.0f, 0.0f}
    };

    for(int i = 0; i < 8; ++i) {
        positions.push_back(cube_pos[i].x);
        positions.push_back(cube_pos[i].y);
        positions.push_back(cube_pos[i].z);

        colors.push_back(cube_colors[i].x);
        colors.push_back(cube_colors[i].y);
        colors.push_back(cube_colors[i].z);

        uv.push_back(cube_uv[i].x);
        uv.push_back(cube_uv[i].y);
    }

    //indices.push_back(0);
    //indices.push_back(1);
    //indices.push_back(2);

    //Front
    indices.push_back(4);
    indices.push_back(5);
    indices.push_back(6);

    indices.push_back(4);
    indices.push_back(7);
    indices.push_back(5);

    //Back
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    indices.push_back(0);
    indices.push_back(3);
    indices.push_back(1);

    //Left
    indices.push_back(3);
    indices.push_back(6);
    indices.push_back(1);

    indices.push_back(3);
    indices.push_back(4);
    indices.push_back(6);

    //Right
    indices.push_back(2);
    indices.push_back(7);
    indices.push_back(0);

    indices.push_back(2);
    indices.push_back(5);
    indices.push_back(7);

    //Top
    indices.push_back(1);
    indices.push_back(6);
    indices.push_back(2);

    indices.push_back(6);
    indices.push_back(5);
    indices.push_back(2);

    //Bottom
    indices.push_back(4);
    indices.push_back(3);
    indices.push_back(7);

    indices.push_back(3);
    indices.push_back(0);
    indices.push_back(7);
}
*/

void Chunk::draw(BlockShader &shader) {
    if(!m_entity) {
        throw UninitializedChunkException("Chunk geometry not generated!");
    }

    m_entity->draw(shader);
}
