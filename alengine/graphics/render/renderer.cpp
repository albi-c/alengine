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
        shader_shadow = new Shader("shadow");
        shader_light = new Shader("light");
        shader_post = new Shader("post");

        whole_screen = new VertexBuffer<TexVertex>({3, 2}, WHOLE_SCREEN_VERTICES);

        main_fbo1.init(width, height, false, true);
        main_fbo2.init(width, height, false, true);
        shadow_fbo.init(width, height);
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
            delete shader_shadow;
            delete shader_light;
            delete shader_post;

            main_fbo1.destroy();
            main_fbo2.destroy();
            shadow_fbo.destroy();
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
        if (object.layer < 0) {
            vertex_lists_back.push_back(vertices);
            num_vertices_back += vertices.size();
        } else {
            vertex_lists_front.push_back(vertices);
            num_vertices_front += vertices.size();
        }
    }
    void Renderer::render(Light light, const glm::vec2& translate) {
        light.pos += translate;
        lights.push_back(light);
    }
    void Renderer::render_end() {
        glm::mat4 view = Camera::view();
        glm::mat4 projection = Camera::projection();
        glm::mat4 transform = projection * view;

        // BACK VERTICES

        std::vector<Vertex> vertices_back;
        vertices_back.reserve(num_vertices_back);

        for (auto& vl : vertex_lists_back) {
            vertices_back.insert(vertices_back.end(), vl.begin(), vl.end());
        }

        VertexBuffer buffer_back({3, 3}, vertices_back);

        // FRONT VERTICES

        std::vector<Vertex> vertices_front;
        vertices_front.reserve(num_vertices_front);

        for (auto& vl : vertex_lists_front) {
            vertices_front.insert(vertices_front.end(), vl.begin(), vl.end());
        }

        VertexBuffer buffer_front({3, 3}, vertices_front);

        // SHADOW PASS (DISABLED)

        // std::vector<glm::vec4> shadow_lines;
        // for (int i = 0; i < vertices_front.size(); i += 3) {
        //     if (vertices_front[i].position.z < -0.1)
        //         continue;
            
        //     shadow_lines.push_back({vertices_front[i + 0].position.xy(), vertices_front[i + 1].position.xy()});
        //     shadow_lines.push_back({vertices_front[i + 1].position.xy(), vertices_front[i + 2].position.xy()});
        //     shadow_lines.push_back({vertices_front[i + 0].position.xy(), vertices_front[i + 2].position.xy()});
        // }

        // std::vector<glm::vec3> shadow_vertices;
        // shadow_vertices.reserve(shadow_lines.size() * 6);
        // for (auto& line : shadow_lines) {
        //     shadow_vertices.push_back({line.xy(), 0.0f});
        //     shadow_vertices.push_back({line.zw(), 0.0f});
        //     shadow_vertices.push_back({line.zw(), 1.0f});

        //     shadow_vertices.push_back({line.xy(), 0.0f});
        //     shadow_vertices.push_back({line.zw(), 1.0f});
        //     shadow_vertices.push_back({line.xy(), 1.0f});
        // }

        // VertexBuffer shadow_buffer({3}, shadow_vertices);

        // shader_shadow->uniform("transform", transform);

        // shadow_fbo.bind();

        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // glDisable(GL_DEPTH_TEST);
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        // shader_shadow->use();

        // for (auto& light : lights) {
        //     shader_shadow->uniform("light_pos", light.pos);
        //     shadow_buffer.draw();
        // }

        // glDisable(GL_BLEND);
        // glEnable(GL_DEPTH_TEST);

        // shadow_fbo.unbind();

        // LIGHTING PASS

        shader_light->uniform("projection", projection);
        shader_light->uniform("view", Camera::view(true));

        light_fbo.bind();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, shadow_fbo.tex());

        shader_light->uniform("tex_shadow", 0);

        VertexBuffer<glm::vec4> light_vertex_buffer({2, 2}, {
            {0.0f, 0.0f,  0.0f, 0.0f},
            {0.0f, (float)height,  0.0f, 1.0f},
            {(float)width, (float)height,  1.0f, 1.0f},
            {0.0f, 0.0f,  0.0f, 0.0f},
            {(float)width, (float)height,  1.0f, 1.0f},
            {(float)width, 0.0f,  1.0f, 0.0f}
        });
        shader_light->use();

        for (auto& light : lights) {
            shader_light->uniform("light_pos", light.pos);
            shader_light->uniform("light_range", light.range);
            shader_light->uniform("light_color", light.color);

            light_vertex_buffer.draw();
        }

        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);

        light_fbo.unbind();

        // MAIN PASS

        shader->uniform("transform", transform);

        // BACK

        main_fbo1.bind();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();
        buffer_back.draw();

        main_fbo1.unbind();

        // FRONT

        main_fbo2.bind();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();
        buffer_front.draw();

        main_fbo2.unbind();

        // POSTPROCESSING PASS

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, main_fbo1.tex());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, main_fbo2.tex());

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, main_fbo1.tex_depth());
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, main_fbo2.tex_depth());

        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, light_fbo.tex());

        shader_post->uniform("tex_main1", 0);
        shader_post->uniform("tex_main2", 1);

        shader_post->uniform("tex_depth1", 2);
        shader_post->uniform("tex_depth2", 3);

        shader_post->uniform("tex_light", 4);

        shader_post->use();
        whole_screen->draw();
        
        // END

        lights.clear();

        vertex_lists_back.clear();
        num_vertices_back = 0;

        vertex_lists_front.clear();
        num_vertices_front = 0;
    }

    void Renderer::resize(int width, int height) {
        Renderer::width = width;
        Renderer::height = height;

        glViewport(0, 0, width, height);

        main_fbo1.destroy();
        main_fbo1.init(width, height, false, true);

        main_fbo2.destroy();
        main_fbo2.init(width, height, false, true);

        shadow_fbo.destroy();
        shadow_fbo.init(width, height);

        light_fbo.destroy();
        light_fbo.init(width, height);
    }
};
