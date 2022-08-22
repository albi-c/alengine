#include "renderer.hpp"

#include "graphics/opengl.hpp"
#include "camera/camera.hpp"

namespace ae {
    void Renderer::init() {
        resize(1, 1);

        glDisable(GL_CULL_FACE);
        glEnable(GL_MULTISAMPLE);
    }

    void Renderer::render_start() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void Renderer::render(std::shared_ptr<Drawable>& object) {
        objects.push_back(object);
    }
    void Renderer::render_end() {
        glm::mat4 transform = Camera::projection() * Camera::view();

        int num_vertices = 0; 

        for (auto& object : objects) {
            num_vertices += object->num_vectices();
        }

        std::vector<Vertex> vertices(num_vertices);

        for (auto& object : objects) {
            auto vert = object->vertices();
            vertices.insert(vertices.end(), vert.begin(), vert.end());
        }

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

        glDrawArrays(GL_TRIANGLES, 0, num_vertices);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

        objects.clear();
    }

    void Renderer::resize(int width, int height) {
        Renderer::width = width;
        Renderer::height = height;

        glViewport(0, 0, width, height);
    }
};
