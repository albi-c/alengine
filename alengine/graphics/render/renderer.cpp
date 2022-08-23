#include "renderer.hpp"

#include "graphics/opengl.hpp"
#include "camera/camera.hpp"

namespace ae {
    void Renderer::init() {
        resize(1, 1);

        shader = new Shader("color");

        initialized = true;

        glEnable(GL_MULTISAMPLE);
        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
    }
    void Renderer::destroy() {
        if (initialized) {
            initialized = false;
            delete shader;
        }
    }

    void Renderer::render_start() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void Renderer::render(const Renderable& object, const glm::vec2& translate) {
        auto vertices = object.vertices();
        if (translate != glm::vec2(0.0f)) {
            std::vector<Vertex> t_vertices;
            t_vertices.reserve(vertices.size());
            for (auto& v : vertices) {
                t_vertices.push_back({v.position + glm::vec3(translate, 0.0f), v.color});
            }
            vertices = t_vertices;
        }
        vertex_lists.push_back(vertices);
        num_vertices += vertices.size();
    }
    void Renderer::render_end() {
        glm::mat4 transform = Camera::projection() * Camera::view();

        std::vector<Vertex> vertices;
        vertices.reserve(num_vertices);

        for (auto& vl : vertex_lists) {
            vertices.insert(vertices.end(), vl.begin(), vl.end());
        }

        shader->uniform("transform", transform);

        GLuint VAO, VBO;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glEnableVertexAttribArray(1);

        shader->use();
        glDrawArrays(GL_TRIANGLES, 0, num_vertices);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

        vertex_lists.clear();
        num_vertices = 0;
    }

    void Renderer::resize(int width, int height) {
        Renderer::width = width;
        Renderer::height = height;

        glViewport(0, 0, width, height);
    }
};
