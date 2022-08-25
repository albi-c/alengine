#include "renderer.hpp"

namespace ae {
    static constexpr int CIRCLE_STEP = 3;
    static constexpr int CIRCLE_VERTICES = 1080 / CIRCLE_STEP;
    static constexpr int CIRCLE_STEPS = 360 / CIRCLE_STEP;

    static constexpr float LINE_WIDTH = 1.0f;

    std::vector<Renderer::RendererVertex> Renderer::get_vertices_rect() {
        return {
            {{0.0f, 0.0f}, {0.0f, 0.0f}},
            {{0.0f, 1.0f}, {0.0f, 1.0f}},
            {{1.0f, 1.0f}, {1.0f, 1.0f}},
            {{0.0f, 0.0f}, {0.0f, 0.0f}},
            {{1.0f, 1.0f}, {1.0f, 1.0f}},
            {{1.0f, 0.0f}, {1.0f, 0.0f}}
        };
    }
    std::vector<Renderer::RendererVertex> Renderer::get_vertices_circle() {
        std::vector<Renderer::RendererVertex> vertices;
        vertices.reserve(CIRCLE_VERTICES);
        for (int i = 0; i < CIRCLE_STEPS; i++) {
            float r1 = glm::radians((float)(i * CIRCLE_STEP));
            float r2 = glm::radians((float)(i * CIRCLE_STEP + CIRCLE_STEP));
            glm::vec2 c1 = glm::vec2(cos(r1), sin(r1));
            glm::vec2 c2 = glm::vec2(cos(r2), sin(r2));

            vertices.push_back({{0.0f, 0.0f}, {0.5f, 0.5f}});
            vertices.push_back({c1, (c1 + 1.0f) / 2.0f});
            vertices.push_back({c2, (c2 + 1.0f) / 2.0f});
        }
        return vertices;
    }
    std::vector<Renderer::RendererVertex> Renderer::get_vertices_line() {
        return get_vertices_rect();
    }
};
