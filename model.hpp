#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include <vector>
#include "glad/glad.h"

class Model {
    private:
        GLsizei m_num_vertices;
        GLuint m_vao;
        std::vector<GLuint> m_vbos;

        void createVbo(int index, int num_scalars_per_vertex, const std::vector<GLfloat> &data);
    public:
        Model(  const std::vector<GLuint> &indices,
                const std::vector<GLfloat> &positions,
                const std::vector<GLfloat> &colors);
        ~Model();

        Model(const Model &) = delete;
        Model & operator=(const Model &) = delete;
        Model(Model &&rhs);
        Model & operator=(Model &&rhs) = delete;

        inline GLuint getVao() const { return m_vao; }
        inline GLsizei getNumVertices() const { return m_num_vertices; }

        void draw() const;
};

/*
#include <vector>
#include "glad/glad.h"

class Model {
    private:
        GLuint m_num_vertices;
        GLuint m_vao_id;
    public:
        Model(const std::vector<GLfloat> &vertices);
        ~Model();

        Model(const Model &) = delete;
        Model & operator=(const Model &) = delete;
        Model(Model &&) = delete;
        Model & operator=(Model &&) = delete;

        void draw();
};
*/

#endif // MODEL_HPP_INCLUDED
