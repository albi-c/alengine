#pragma once

#include <vector>

#include "graphics/opengl.hpp"

namespace ae {
    class TextureBuffer {
    public:
        GLuint buffer, texture;

        TextureBuffer(const std::vector<float>& data);
        TextureBuffer(const void* data, std::size_t length);

        void bind();
    };
};
