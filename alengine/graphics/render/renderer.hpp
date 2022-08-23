#pragma once

#include "renderable.hpp"
#include "graphics/shaders/shader.hpp"

#include <memory>

namespace ae {
    class Renderer {
    public:
        static void init();
        static void destroy();

        static void render_start();
        static void render(const Renderable& object, const glm::vec2& translate = glm::vec2(0.0f));
        static void render_end();

        static void resize(int width, int height);
    
    private:
        static inline int width, height;

        static inline bool initialized = false;

        static inline int num_vertices = 0;
        static inline std::vector<std::vector<Vertex>> vertex_lists;

        static inline Shader* shader;
    };
};
