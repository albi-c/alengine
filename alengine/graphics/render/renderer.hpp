#pragma once

#include "renderable.hpp"
#include "material.hpp"
#include "graphics/shaders/shader.hpp"
#include "graphics/framebuffer/framebuffer.hpp"
#include "graphics/buffer/vertex.hpp"

// #include "shapes.hpp"
#include "objects/shapes.hpp"
#include "objects/light.hpp"

#include <memory>
#include <utility>
#include <vector>

namespace ae {
    struct RendererVertex;

    class Renderer {
    public:
        static void init();
        static void destroy();

        static void render(const Rect& rect);
        static void render(const Circle& circle);
        static void render(const Line& line);

        static void render(const Light& light);

        static void render_start();
        static void render_end();

        static void resize(int width, int height);
    
    private:
        static inline int width, height;

        static inline bool initialized = false;

        static inline std::vector<Rect> rects;
        static inline std::vector<Circle> circles;
        static inline std::vector<Line> lines;

        static inline std::vector<Light> lights;

        static inline Shader* shader;
        static inline Shader* shader_light;
        static inline Shader* shader_post;

        static inline Framebuffer main_fbo;
        static inline Framebuffer light_fbo;

        static inline VertexBuffer<std::pair<glm::vec2, glm::vec2>>* whole_screen;

        struct RendererVertex {
            glm::vec2 pos;
            glm::vec2 tex;
        };

        static std::vector<RendererVertex> get_vertices_rect();
        static std::vector<RendererVertex> get_vertices_circle();
        static std::vector<RendererVertex> get_vertices_line();

        static inline VertexBuffer<RendererVertex>* buffer_rect;
        static inline VertexBuffer<RendererVertex>* buffer_circle;
        static inline VertexBuffer<RendererVertex>* buffer_line;
    };
};
