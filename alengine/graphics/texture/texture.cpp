#include "texture.hpp"

#include "stb/stb_image.h"
#include "util/util.hpp"

namespace ae {
    Texture::Texture(Texture* other)
        : texture(other->texture) {}
    Texture::Texture(const std::string& filename) {
        stbi_set_flip_vertically_on_load(true);
        int width, height;
        unsigned char* data = stbi_load(filename.c_str(), &width, &height, nullptr, 4);
        if (data == nullptr) {
            log::e("Failed to load texture '" + filename + "'");
            return;
        }

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }
    Texture::~Texture() {
        glDeleteTextures(1, &texture);
    }

    void Texture::bind() const {
        glBindTexture(GL_TEXTURE_2D, texture);
    }
};
