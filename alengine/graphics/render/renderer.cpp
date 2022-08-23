#include "renderer.hpp"

#include "graphics/opengl.hpp"
#include "camera/camera.hpp"

namespace ae {
    static const std::vector<TexVertex> WHOLE_SCREEN_VERTICES = {
        {{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
        {{-1.0f,  1.0f, 0.0f}, {0.0f, 1.0f}},
        {{ 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
        {{ 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f}},
        {{ 1.0f, -1.0f, 0.0f}, {1.0f, 0.0f}}
    };

    void Renderer::init() {
        resize(1, 1);

        shader = new Shader("color");
        shader_post = new Shader("post");

        whole_screen = new VertexBuffer<TexVertex>({3, 2}, WHOLE_SCREEN_VERTICES);

        light_fbo.init(width, height);

        initialized = true;

        glEnable(GL_MULTISAMPLE);
        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
    }
    void Renderer::destroy() {
        if (initialized) {
            initialized = false;
            delete shader;
            delete shader_post;
            light_fbo.destroy();
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

        const Light* light_p = object.light();
        if (light_p != nullptr) {
            Light light = *object.light();
            light.pos += translate;
            lights.push_back(light);
        }
    }
    void Renderer::render_end() {
        glm::mat4 transform = Camera::projection() * Camera::view();

        light_fbo.bind();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // TODO: render lights, light shader
        for (auto& light : lights) {
            //
        }

        light_fbo.unbind();

        std::vector<Vertex> vertices;
        vertices.reserve(num_vertices);

        for (auto& vl : vertex_lists) {
            vertices.insert(vertices.end(), vl.begin(), vl.end());
        }

        shader->uniform("transform", transform);

        VertexBuffer buffer({3, 3}, vertices);

        shader->use();
        buffer.draw();

        vertex_lists.clear();
        num_vertices = 0;
    }

    void Renderer::resize(int width, int height) {
        Renderer::width = width;
        Renderer::height = height;

        glViewport(0, 0, width, height);

        light_fbo.destroy();
        light_fbo.init(width, height);
    }
};
