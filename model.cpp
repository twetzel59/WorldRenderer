#include "model.hpp"
#include <iostream>

Model::Model(const std::vector<GLuint> &indices,
             const std::vector<GLfloat> &positions,
             const std::vector<GLfloat> &colors) {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo_indices;
    glGenBuffers(1, &vbo_indices);
    m_vbos.push_back(vbo_indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof (GLuint), indices.data(), GL_STATIC_DRAW);

    createVbo(0, 3, positions);
    //createVbo(1, 3, colors);

    //THIS CAN NOT BE REORDERED!!! VERTEX ARRAY WILL REMEMBER UNBIND, CAUSING SEGFAULT!!!
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    m_num_vertices = indices.size();
    m_vao = vao;
}

Model::Model(Model &&rhs)
    :   m_num_vertices(rhs.m_num_vertices),
        m_vao(rhs.m_vao),
        m_vbos(rhs.m_vbos)
{
    rhs.m_num_vertices = 0;
    rhs.m_vao = 0;
    rhs.m_vbos.clear();
}

Model::~Model() {
    if(m_vbos.size()) {
        for(GLuint i : m_vbos) {
            std::cout << "vbo: " << i << std::endl;
        }

        glDeleteBuffers(m_vbos.size(), m_vbos.data());
    }

    if(m_vao) {
        std::cout << "vao: " << m_vao;
        glDeleteVertexArrays(1, &m_vao);
    }
}

void Model::createVbo(int index, int num_scalars_per_vertex, const std::vector<GLfloat> &data) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    m_vbos.push_back(vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof (GLfloat), data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(index, num_scalars_per_vertex, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::draw() const {
    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);
    glDrawElements(GL_TRIANGLES, m_num_vertices, GL_UNSIGNED_INT, nullptr);
    //glDrawArrays(GL_TRIANGLES, 0, m_num_vertices);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}
