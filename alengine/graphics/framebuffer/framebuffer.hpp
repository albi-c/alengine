#pragma once

#include "graphics/opengl.hpp"

namespace ae {
    class Framebuffer {
    public:
        ~Framebuffer();

        void init(int width, int height, bool depth_only = false, bool depth_texture = false);
        void destroy();

        void bind();
        void unbind();

        GLuint tex();
        GLuint tex_depth();
    
    private:
        int width, height;

        bool initialized = false;

        GLuint fbo;
        GLuint rbo;
        GLuint texture, texture_depth;
    };
};
