#include "texture.hpp"

namespace ae {
    TextureBuffer::TextureBuffer(const std::vector<float>& data)
        : TextureBuffer(&data[0], data.size() * sizeof(float)) {}
    TextureBuffer::TextureBuffer(const void* data, std::size_t length) {
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_TEXTURE_BUFFER, buffer);
        glBufferData(GL_TEXTURE_BUFFER, length, data, GL_STATIC_DRAW);

        glGenTextures(1, &texture);
    }

    void TextureBuffer::bind() {
        glBindTexture(GL_TEXTURE_BUFFER, texture);
        glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, buffer);
    }
};
