#include "renderer.hpp"

#include "graphics/opengl.hpp"
#include "camera/camera.hpp"
#include "graphics/buffer/texture.hpp"

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
        shader_light = new Shader("light");
        shader_post = new Shader("post");

        whole_screen = new VertexBuffer<TexVertex>({3, 2}, WHOLE_SCREEN_VERTICES);

        main_fbo.init(width, height);
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
            delete shader_light;
            delete shader_post;

            main_fbo.destroy();
            light_fbo.destroy();
        }
    }

    void Renderer::render_start() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
    void Renderer::render(Light light, const glm::vec2& translate) {
        light.pos += translate;
        lights.push_back(light);
    }
    void Renderer::render_end() {
        glm::mat4 view = Camera::view();
        glm::mat4 projection = Camera::projection();
        glm::mat4 transform = projection * view;

        std::vector<Vertex> vertices;
        vertices.reserve(num_vertices);

        for (auto& vl : vertex_lists) {
            vertices.insert(vertices.end(), vl.begin(), vl.end());
        }

        VertexBuffer buffer({3, 3}, vertices);

        // LIGHTING PASS

        TextureBuffer lights_tex(&lights[0], lights.size() * sizeof(Light));

        glActiveTexture(GL_TEXTURE0);
        lights_tex.bind();

        shader_light->uniform("lights", 0);
        shader_light->uniform("n_lights", (int)lights.size());

        shader_light->uniform("projection", projection);
        shader_light->uniform("view", Camera::view(true));

        light_fbo.bind();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        VertexBuffer<glm::vec2> light_vertex_buffer({2}, {
            {0.0f, 0.0f},
            {0.0f, (float)height},
            {(float)width, (float)height},
            {0.0f, 0.0f},
            {(float)width, (float)height},
            {(float)width, 0.0f}
        });
        shader_light->use();
        light_vertex_buffer.draw();

        light_fbo.unbind();

        // MAIN PASS

        shader->uniform("transform", transform);

        main_fbo.bind();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();
        buffer.draw();

        main_fbo.unbind();

        // POSTPROCESSING PASS

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, main_fbo.tex());

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, light_fbo.tex());

        shader_post->uniform("tex_main", 0);
        shader_post->uniform("tex_light", 1);

        shader_post->use();
        whole_screen->draw();


        lights.clear();
        vertex_lists.clear();
        num_vertices = 0;
    }

    void Renderer::resize(int width, int height) {
        Renderer::width = width;
        Renderer::height = height;

        glViewport(0, 0, width, height);

        main_fbo.destroy();
        main_fbo.init(width, height);

        light_fbo.destroy();
        light_fbo.init(width, height);
    }
};
