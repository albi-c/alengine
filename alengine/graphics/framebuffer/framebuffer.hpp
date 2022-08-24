#pragma once

#include "graphics/opengl.hpp"

namespace ae {
    class Framebuffer {
    public:
        ~Framebuffer();

        void init(int width, int height, bool depth_only = false);
        void destroy();

        void bind();
        void unbind();

        GLuint tex();
    
    private:
        int width, height;

        bool initialized = false;

        GLuint fbo;
        GLuint rbo;
        GLuint texture;
    };
};
