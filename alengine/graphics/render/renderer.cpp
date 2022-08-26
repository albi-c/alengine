#include "renderer.hpp"

#include "graphics/opengl.hpp"
#include "camera/camera.hpp"
#include "graphics/buffer/texture.hpp"

namespace ae {
    static const std::vector<std::pair<glm::vec2, glm::vec2>> WHOLE_SCREEN_VERTICES = {
        {{-1.0f, -1.0f}, {0.0f, 0.0f}},
        {{-1.0f,  1.0f}, {0.0f, 1.0f}},
        {{ 1.0f,  1.0f}, {1.0f, 1.0f}},
        {{-1.0f, -1.0f}, {0.0f, 0.0f}},
        {{ 1.0f,  1.0f}, {1.0f, 1.0f}},
        {{ 1.0f, -1.0f}, {1.0f, 0.0f}}
    };

    void Renderer::init() {
        resize(1, 1);

        shader = new Shader("main");
        shader_light = new Shader("light");
        shader_post = new Shader("post");

        whole_screen = new VertexBuffer({2, 2}, WHOLE_SCREEN_VERTICES);

        buffer_rect = new VertexBuffer({2, 2}, get_vertices_rect());
        buffer_circle = new VertexBuffer({2, 2}, get_vertices_circle());
        buffer_line = new VertexBuffer({2, 2}, get_vertices_line());

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

            delete whole_screen;
            
            delete buffer_rect;
            delete buffer_circle;
            delete buffer_line;

            main_fbo.destroy();
            light_fbo.destroy();
        }
    }

    void Renderer::render(const Rect& rect) {
        rects[rect.mat.texture].push_back(rect);
    }
    void Renderer::render(const Circle& circle) {
        circles[circle.mat.texture].push_back(circle);
    }
    void Renderer::render(const Line& line) {
        lines[line.mat.texture].push_back(line);
    }

    // void Renderer::render(const std::vector<Rect>& rects) {
    //     for (auto& rect : rects) {
    //         render(rect);
    //     }
    // }
    // void Renderer::render(const std::vector<Circle>& circles) {
    //     for (auto& circle : circles) {
    //         render(circle);
    //     }
    // }
    // void Renderer::render(const std::vector<Line>& lines) {
    //     for (auto& line : lines) {
    //         render(line);
    //     }
    // }

    void Renderer::render(const Light& light) {
        lights.push_back(light);
    }

    void Renderer::render_start() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }
    void Renderer::render_end() {
        glm::mat4 view = Camera::view();
        glm::mat4 projection = Camera::projection();
        glm::mat4 transform = projection * view;

        // LIGHTING PASS

        shader_light->uniform("projection", projection);
        shader_light->uniform("view", Camera::view(true));

        light_fbo.bind();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

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

        shader->uniform("texture1", 0);

        main_fbo.bind();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto& [tex, rectv] : rects) {
            if (tex) {
                glActiveTexture(GL_TEXTURE0);
                tex->bind();

                shader->uniform("texture_enabled", true);
            } else {
                shader->uniform("texture_enabled", false);
            }
            for (auto& rect : rectv) {
                shader->uniform("model", glm::translate(glm::scale(glm::mat4(1.0f), {rect.size, 1.0f}), {rect.pos / rect.size, 1.0f}));
                shader->uniform("layer", (float)rect.layer);
                
                shader->uniform("color", rect.mat.color);

                shader->uniform("texture_repeat", rect.mat.texture_repeat);

                buffer_rect->draw();
            }
        }
        for (auto& [tex, circlev] : circles) {
            if (tex) {
                glActiveTexture(GL_TEXTURE0);
                tex->bind();

                shader->uniform("texture_enabled", true);
            } else {
                shader->uniform("texture_enabled", false);
            }
            for (auto& circle : circlev) {
                shader->uniform("model", glm::translate(glm::scale(glm::mat4(1.0f), {glm::vec2(circle.rad), 1.0f}), {circle.pos / circle.rad, 1.0f}));
                shader->uniform("layer", (float)circle.layer);

                shader->uniform("color", circle.mat.color);

                shader->uniform("texture_repeat", circle.mat.texture_repeat);

                buffer_circle->draw();
            }
        }

        main_fbo.unbind();

        // POSTPROCESSING PASS

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, main_fbo.tex());

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, light_fbo.tex());

        shader_post->uniform("tex_main1", 0);

        shader_post->uniform("tex_light", 1);

        shader_post->use();
        whole_screen->draw();
        
        // END

        rects.clear();
        circles.clear();
        lines.clear();

        lights.clear();
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
