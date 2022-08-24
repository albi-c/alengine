#pragma once

#include <vector>

#include "graphics/opengl.hpp"

namespace ae {
    template <class T, int V = GL_TRIANGLES>
    class VertexBuffer {
    public:
        GLuint VAO, VBO;

        VertexBuffer(std::vector<int> sizes, std::vector<T> vertices) {
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), vertices.data(), GL_STATIC_DRAW);

            int stride = 0;
            for (auto& size : sizes) {
                stride += size;
            }

            int offset = 0, i = 0;
            for (auto& size : sizes) {
                glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
                glEnableVertexAttribArray(i);

                i++;
                offset += size;
            }

            num_vertices = vertices.size();
        }
        ~VertexBuffer() {
            glDeleteBuffers(1, &VBO);
            glDeleteVertexArrays(1, &VAO);
        }

        void draw() const {
            glBindVertexArray(VAO);
            glDrawArrays(V, 0, num_vertices);
        }
    
    private:
        int num_vertices;
    };
};
